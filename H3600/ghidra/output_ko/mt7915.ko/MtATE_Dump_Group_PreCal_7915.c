// module: mt7915.ko
// function: MtATE_Dump_Group_PreCal_7915 @ 0x28b184
// size: 160 bytes
//

void MtATE_Dump_Group_PreCal_7915(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)("RTMPSetSTAPassPhrase" + param_1 + 8);
  if (-1 < DebugLevel) {
    printk("%s: Group Pre-Cal: \n","MtATE_Dump_Group_PreCal_7915");
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
  } while (iVar1 != iVar3 + 0xc400);
  return;
}

