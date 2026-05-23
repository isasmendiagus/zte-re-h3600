// module: mt7915.ko
// function: CmdMultipleMacRegAccessReadCb @ 0x1ab670
// size: 144 bytes
//

void CmdMultipleMacRegAccessReadCb(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  uVar1 = (param_3 - 0x14U) / 0xc;
  if (uVar1 != 0) {
    iVar5 = *(int *)(param_1 + 0xc) + 8;
    iVar6 = *(int *)(param_1 + 0xc) + (uVar1 + 1) * 8;
    iVar2 = param_2 + 0x14;
    iVar3 = iVar5;
    do {
      iVar4 = iVar3 + 8;
      *(undefined4 *)(iVar3 + -8) = *(undefined4 *)(iVar2 + 4);
      *(undefined4 *)(iVar3 + -4) = *(undefined4 *)(iVar2 + 8);
      iVar2 = iVar2 + 0xc;
      iVar3 = iVar4;
    } while (iVar4 != iVar6);
    do {
      if (2 < DebugLevel) {
        printk("0x%08x=0x%08x\n",*(undefined4 *)(iVar5 + -8),*(undefined4 *)(iVar5 + -4));
      }
      iVar5 = iVar5 + 8;
    } while (iVar5 != iVar6);
    return;
  }
  return;
}

