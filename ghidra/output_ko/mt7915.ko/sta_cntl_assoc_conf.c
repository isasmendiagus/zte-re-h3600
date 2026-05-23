// module: mt7915.ko
// function: sta_cntl_assoc_conf @ 0x737a4
// size: 404 bytes
//

void sta_cntl_assoc_conf(void *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  short local_22 [3];
  
  iVar4 = *(int *)((int)param_1 + 0x92c);
  uVar5 = *(undefined4 *)(iVar4 + 8);
  iVar1 = GetStaCfgByWdev(uVar5,iVar4);
  if (iVar1 != 0) {
    iVar2 = GetAssociatedAPByWdev(uVar5,iVar4);
    os_move_mem(local_22,param_1,2);
    if (local_22[0] == 0) {
      LinkUp(uVar5,1,iVar4,0,param_1);
      cntl_fsm_state_transition(iVar4,0,"sta_cntl_assoc_conf");
      if (2 < DebugLevel) {
        printk("CNTL - Association successful on BSS #%ld\n",*(undefined4 *)(iVar1 + 0x211e40));
      }
    }
    else {
      if (2 < DebugLevel) {
        printk("CNTL - Association fails on BSS #%ld Reason(%d)\n",*(undefined4 *)(iVar1 + 0x211e40)
               ,local_22[0]);
      }
      iVar3 = *(int *)(iVar4 + 0x14);
      if (iVar3 == 2 && iVar2 != 0) {
        MacTableDeleteEntry(uVar5,*(undefined2 *)(iVar2 + 0xe0),iVar2 + 0xec);
        iVar3 = *(int *)(iVar4 + 0x14);
      }
      if ((iVar3 == 0x100) &&
         (HW_REMOVE_REPT_ENTRY(uVar5,*(undefined1 *)(iVar4 + 0xe)), -1 < DebugLevel)) {
        printk("%s:wdev(type=%d,func_idx=%d)assoc fail reason(%d) and free rept_entry\n",
               "sta_cntl_assoc_conf",*(undefined4 *)(iVar4 + 0x14),*(undefined1 *)(iVar4 + 0xe),
               local_22[0]);
      }
      *(int *)(iVar1 + 0x211e40) = *(int *)(iVar1 + 0x211e40) + 1;
      IterateOnBssTab(uVar5,iVar4);
    }
    return;
  }
  printk(&_LC1,0x617);
  dump_stack();
  return;
}

