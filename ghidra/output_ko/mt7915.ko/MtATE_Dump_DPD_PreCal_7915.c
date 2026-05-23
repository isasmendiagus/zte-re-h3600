// module: mt7915.ko
// function: MtATE_Dump_DPD_PreCal_7915 @ 0x28b40c
// size: 160 bytes
//

void MtATE_Dump_DPD_PreCal_7915(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)("RTMPSetSTAPassPhrase" + param_1 + 0x10);
  if (-1 < DebugLevel) {
    printk("%s: DPD/Flatness Pre-Cal: \n","MtATE_Dump_DPD_PreCal_7915");
  }
  iVar2 = 0;
  iVar1 = iVar3;
  do {
    if (-1 < DebugLevel) {
      printk("[0x%08x] 0x%8x 0x%8x 0x%8x 0x%8x\n",iVar2,*(undefined4 *)(iVar3 + iVar2),
             *(undefined4 *)(iVar1 + 4),*(undefined4 *)(iVar1 + 8),*(undefined4 *)(iVar1 + 0xc));
    }
    iVar1 = iVar1 + 0x10;
    iVar2 = iVar2 + 0x10;
  } while (iVar1 != iVar3 + 0xd800);
  return;
}

