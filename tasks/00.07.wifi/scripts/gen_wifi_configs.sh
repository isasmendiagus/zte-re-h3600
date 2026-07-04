#!/bin/sh
# Render the STAGE-2 WiFi configs from configs/*.template, injecting the WPA
# passphrase from the git-ignored secret (scratchpad/.wifi_psk) or $WIFI_PSK.
# Output goes to tasks/00.07.wifi/out/ (git-ignored). The rendered files are
# what later gets copied to the device (/etc/) during the ON-DEVICE phase —
# this script itself never touches the device.
set -eu

TASK_DIR=$(cd "$(dirname "$0")/.." && pwd)
REPO_ROOT=$(cd "$TASK_DIR/../.." && pwd)
PSK_FILE="$REPO_ROOT/scratchpad/.wifi_psk"

if [ -n "${WIFI_PSK:-}" ]; then
    PSK="$WIFI_PSK"
elif [ -f "$PSK_FILE" ]; then
    PSK=$(cat "$PSK_FILE")
else
    echo "ERROR: no passphrase. Set \$WIFI_PSK or create $PSK_FILE (chmod 600)." >&2
    exit 1
fi

# Escape sed replacement metacharacters (\, &, and the | delimiter).
PSK_ESC=$(printf '%s' "$PSK" | sed -e 's/[\\&|]/\\&/g')

OUT_DIR="$TASK_DIR/out"
mkdir -p "$OUT_DIR"

for tpl in "$TASK_DIR"/configs/*.template; do
    out="$OUT_DIR/$(basename "$tpl" .template)"
    sed "s|@WIFI_PSK@|$PSK_ESC|g" "$tpl" > "$out"
    chmod 600 "$out"
    echo "rendered: $out"
done

# Safety net: the placeholder must be gone and the PSK must not exist in any
# tracked file (templates stay secret-free).
if grep -rl '@WIFI_PSK@' "$OUT_DIR" >/dev/null 2>&1; then
    echo "ERROR: placeholder left unrendered in $OUT_DIR" >&2
    exit 1
fi
if git -C "$REPO_ROOT" grep -qF "$PSK" -- . 2>/dev/null; then
    echo "ERROR: PSK literal found in a git-tracked file! Fix before committing." >&2
    exit 1
fi
echo "OK: PSK not present in any git-tracked file."
