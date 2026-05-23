// module: mt7915.ko
// function: DfsIsOutBandAvailable @ 0x23478c
// size: 100 bytes
//

bool DfsIsOutBandAvailable(int param_1,undefined4 param_2)

{
  byte *pbVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  
  iVar3 = HcGetBandByWdev(param_2);
  bVar2 = *(short *)(param_1 + 0x795402) == 1;
  bVar5 = !bVar2;
  if (bVar5) {
    uVar4 = (uint)*(byte *)(param_1 + 0x795409);
  }
  else {
    uVar4 = param_1 + 0x795000 + iVar3;
  }
  if (!bVar5) {
    pbVar1 = (byte *)(uVar4 + 0x130);
    uVar4 = (uint)*pbVar1;
    *(byte *)(param_1 + 0x795409) = *pbVar1;
  }
  bVar5 = *(byte *)(param_1 + iVar3 + 0x795130) == uVar4;
  if (!bVar5) {
    *(undefined1 *)(param_1 + 0x795409) = 0;
  }
  return bVar5 || bVar2;
}

