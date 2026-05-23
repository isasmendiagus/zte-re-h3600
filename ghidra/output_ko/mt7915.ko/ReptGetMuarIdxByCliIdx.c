// module: mt7915.ko
// function: ReptGetMuarIdxByCliIdx @ 0x81478
// size: 180 bytes
//

int ReptGetMuarIdxByCliIdx(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = *(byte *)(iVar2 + 0x14c);
  if (param_2 < *(byte *)(iVar2 + 0x14a)) {
    iVar4 = param_2 * 0x42f4 + *(int *)(&DAT_003687a8 + param_1);
    if (iVar4 == 0) {
      return 0;
    }
    iVar4 = OcGetRepeaterEntry(*(undefined4 *)(iVar4 + 0xb9c),*(undefined1 *)(iVar4 + 4));
    if (iVar4 == 0) {
      uVar3 = (uint)bVar1 - (uint)*(byte *)(iVar2 + 0x14c);
    }
    else {
      uVar3 = (uint)*(byte *)(iVar4 + 1) - (uint)*(byte *)(iVar2 + 0x14c);
    }
    return (uVar3 & 0x7f) << 1;
  }
  if (-1 < DebugLevel) {
    printk("(%s) Error CliIdx(%d)\n","ReptGetMuarIdxByCliIdx",param_2,DebugLevel,param_4);
    return 0;
  }
  return 0;
}

