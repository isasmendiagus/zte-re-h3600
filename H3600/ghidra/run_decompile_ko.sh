#!/bin/bash
# Decompile named functions from each imported .ko in project_ko
set -e
PROJECT=/home/ubuntu/Projects/MYSELF/ZTE/H3600/ghidra/project_ko
PROJ_NAME=h3600_kmods
SCRIPT=/home/ubuntu/Projects/MYSELF/ZTE/orca_pet/ghidra/scripts/dump_named_funcs.py
OUT=/home/ubuntu/Projects/MYSELF/ZTE/H3600/ghidra/output_ko
GHIDRA=/opt/ghidra_12.0.4_PUBLIC/support/analyzeHeadless

mkdir -p "$OUT"

for KO in switch.ko plat-zxylzb_9128S.ko tm.ko idmfdb.ko zx_ponreg.ko rtkatm.ko mt7915.ko wlan_debug_module.ko; do
  echo "=== $KO ==="
  "$GHIDRA" "$PROJECT" "$PROJ_NAME" \
    -process "$KO" -noanalysis \
    -scriptPath "$(dirname "$SCRIPT")" \
    -postScript "$(basename "$SCRIPT")" "$OUT" \
    -max-cpu 12 2>&1 | tail -8
done
echo "ALL DONE"
ls -la "$OUT"
