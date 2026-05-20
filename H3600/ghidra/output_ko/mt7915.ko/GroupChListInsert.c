// module: mt7915.ko
// function: GroupChListInsert @ 0x22d820
// size: 216 bytes
//

void GroupChListInsert(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  
  iVar1 = DebugLevel;
  uVar2 = *(byte *)(param_1 + 0xa795e4) + 1;
  iVar4 = param_1 + (uint)*(byte *)(param_1 + 0xa795e4) * 0x10;
  *(undefined1 *)(iVar4 + 0xa79234) = *(undefined1 *)(param_2 + 1);
  *(undefined1 *)(iVar4 + 0xa79235) = *(undefined1 *)(param_2 + 2);
  uVar5 = (uint)*(byte *)(param_2 + 5);
  *(byte *)(iVar4 + 0xa79240) = *(byte *)(param_2 + 5);
  *(char *)(param_1 + 0xa795e4) = (char)uVar2;
  if (iVar1 < 3) {
    uVar3 = *(undefined4 *)(param_2 + 0x10);
    *(undefined4 *)(iVar4 + 0xa79238) = uVar3;
    *(undefined4 *)(iVar4 + 0xa7923c) = uVar3;
  }
  else {
    printk("%s Insert new group channel list Number=%d CenChannel=%d BestCtrlChannel=%d SkipGroup=%d\n"
           ,"GroupChListInsert",uVar2 & 0xff,*(undefined1 *)(iVar4 + 0xa79235),
           *(undefined1 *)(iVar4 + 0xa79234),uVar5);
    iVar1 = DebugLevel;
    uVar3 = *(undefined4 *)(param_2 + 0x10);
    *(undefined4 *)(iVar4 + 0xa79238) = uVar3;
    *(undefined4 *)(iVar4 + 0xa7923c) = uVar3;
    if (2 < iVar1) {
      printk("%s ipi_hist_free_cnt=0x%x, ipi_hist_cnt=0x%x, ipi_noisy = 0x%x\n","GroupChListInsert",
             *(undefined4 *)(param_2 + 0xc),*(undefined4 *)(param_2 + 8),uVar3,uVar5);
    }
  }
  return;
}

