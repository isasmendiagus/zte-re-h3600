// module: mt7915.ko
// function: WtcGetMaxStaNum @ 0xadca8
// size: 132 bytes
//

uint WtcGetMaxStaNum(int param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0x4328);
  uVar1 = *(ushort *)(param_1 + 0x1a28);
  uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(iVar5 + 0xa797a0));
  if (uVar3 <= uVar1) {
    if (-1 < DebugLevel) {
      uVar2 = *(undefined2 *)(param_1 + 0x1a28);
      uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(iVar5 + 0xa797a0));
      printk("%s: MaxUcastEntryNum=%d >= WTBL_MAX_NUM(%d)\n","WtcGetMaxStaNum",uVar2,uVar4);
    }
    uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(iVar5 + 0xa797a0));
    return uVar3;
  }
  return (uint)*(ushort *)(param_1 + 0x1a28);
}

