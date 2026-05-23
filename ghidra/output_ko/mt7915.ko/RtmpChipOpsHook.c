// module: mt7915.ko
// function: RtmpChipOpsHook @ 0x147ce8
// size: 276 bytes
//

undefined4 RtmpChipOpsHook(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  DfsSetNewChInit(param_1);
  uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar3 != 0x7628 && uVar3 != 0x7603) {
    uVar2 = uVar3 - 0x7636;
    bVar6 = 0x7605 < uVar3;
    bVar4 = uVar3 == 0x7606;
    if (!bVar4) {
      bVar6 = uVar2 != 0;
    }
    bVar5 = uVar2 == 1;
    if (!bVar6 || (bVar4 || bVar5)) {
      uVar2 = 1;
    }
    if (bVar6 && (!bVar4 && !bVar5)) {
      uVar2 = 0;
    }
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xfffb) == 0x7611) {
      uVar2 = uVar2 | 1;
    }
    if (uVar2 == 0) goto LAB_00147d6c;
  }
  if (0 < DebugLevel) {
    printk("%s(%d): Not support for HIF_MT yet! MACVersion=0x%x\n","RtmpChipOpsHook",0x8c,
           *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 8));
  }
LAB_00147d6c:
  if (*(int *)("Get_RBIST_IQ_Data_Proc" + param_1 + 8) == -1) {
    return 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x794ae0) = 1;
  WfSysPreInit(param_1);
  if (2 < DebugLevel) {
    printk("[PMF] Encryption mode = %d\n",*(undefined1 *)(iVar1 + 0xfb));
    return 0;
  }
  return 0;
}

