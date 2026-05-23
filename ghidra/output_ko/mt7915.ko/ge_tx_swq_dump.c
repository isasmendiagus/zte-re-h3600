// module: mt7915.ko
// function: ge_tx_swq_dump @ 0xd2000
// size: 376 bytes
//

void ge_tx_swq_dump(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  bool bVar6;
  
  iVar4 = param_1 + param_2 * 4 + 0x28633c;
  _raw_spin_lock_bh(iVar4);
  iVar1 = param_1 + param_2 * 0x4018;
  iVar2 = *(int *)(iVar1 + 0x28a350);
  iVar1 = *(int *)(iVar1 + 0x28a34c);
  if (0 < DebugLevel) {
    pcVar5 = "Empty";
    if (*(short *)(param_1 + (iVar2 + param_2 * 0x200c + 0x1431a4) * 2 + 4) != 0) {
      pcVar5 = "HasEntry";
    }
    printk("\nDump TxSwQ[%d]: DeqIdx=%d, EnqIdx=%d, %s\n",param_2,iVar2,iVar1,pcVar5);
  }
  if (iVar2 != iVar1) {
    uVar3 = 1;
    do {
      if (((0 < DebugLevel) &&
          (printk(&_LC29,*(undefined2 *)(param_1 + (iVar2 + param_2 * 0x200c + 0x1431a4) * 2 + 4)),
          0x2000 < uVar3)) && (0 < DebugLevel)) {
        printk("%s(): Buggy here? force break! deq_id=%d, enq_id=%d\n","ge_tx_swq_dump",iVar2,iVar1)
        ;
      }
      bVar6 = iVar2 == 0x1fff;
      iVar2 = iVar2 + 1;
      uVar3 = uVar3 + 1;
      if (bVar6) {
        iVar2 = 0;
      }
    } while (iVar1 != iVar2);
  }
  _raw_spin_unlock_bh(iVar4);
  if (0 < DebugLevel) {
    printk(&_LC7);
    return;
  }
  return;
}

