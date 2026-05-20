// module: mt7915.ko
// function: MacTableSetEntryPhyCfg @ 0x148a50
// size: 196 bytes
//

void MacTableSetEntryPhyCfg(undefined4 param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(param_2 + 0xb7d);
  if (3 < uVar2) {
    *(byte *)(param_2 + 0xbf) = *(byte *)(param_2 + 0xbf) & 0x1f | 0x20;
    bVar1 = OfdmRateToRxwiMCS[uVar2];
    *(byte *)(param_2 + 0xc1) = *(byte *)(param_2 + 0xc1) & 0x1f | 0x20;
    *(byte *)(param_2 + 0xbe) = *(byte *)(param_2 + 0xbe) & 0xc0 | bVar1 & 0x3f;
    bVar1 = OfdmRateToRxwiMCS[uVar2];
    *(byte *)(param_2 + 0xbd) = *(byte *)(param_2 + 0xbd) & 0x1f | 0x20;
    *(byte *)(param_2 + 0xc0) = *(byte *)(param_2 + 0xc0) & 0xc0 | bVar1 & 0x3f;
    *(byte *)(param_2 + 0xbc) = *(byte *)(param_2 + 0xbc) & 0xc0 | OfdmRateToRxwiMCS[uVar2] & 0x3f;
    return;
  }
  bVar1 = *(byte *)(param_2 + 0xb7d) & 0x3f;
  *(byte *)(param_2 + 0xbe) = *(byte *)(param_2 + 0xbe) & 0xc0 | bVar1;
  *(byte *)(param_2 + 0xc0) = *(byte *)(param_2 + 0xc0) & 0xc0 | bVar1;
  *(byte *)(param_2 + 0xbc) = *(byte *)(param_2 + 0xbc) & 0xc0 | bVar1;
  *(byte *)(param_2 + 0xbf) = *(byte *)(param_2 + 0xbf) & 0x1f;
  *(byte *)(param_2 + 0xc1) = *(byte *)(param_2 + 0xc1) & 0x1f;
  *(byte *)(param_2 + 0xbd) = *(byte *)(param_2 + 0xbd) & 0x1f;
  return;
}

