// module: mt7915.ko
// function: sta_cntl_reassoc_conf @ 0x74ca8
// size: 268 bytes
//

void sta_cntl_reassoc_conf(void *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  short local_1a;
  
  iVar2 = *(int *)((int)param_1 + 0x92c);
  uVar3 = *(undefined4 *)(iVar2 + 8);
  iVar1 = GetStaCfgByWdev(uVar3,iVar2);
  if (iVar1 != 0) {
    os_move_mem(&local_1a,param_1,2);
    if (local_1a == 0) {
      LinkUp(uVar3,1,*(undefined4 *)((int)param_1 + 0x92c),0,param_1);
      cntl_fsm_state_transition(iVar2,0,"sta_cntl_reassoc_conf");
      if (2 < DebugLevel) {
        printk("CNTL - Re-assocition successful on BSS #%ld\n",*(undefined4 *)(iVar1 + 0x211e44));
      }
    }
    else {
      if (2 < DebugLevel) {
        printk("CNTL - Re-assocition fails on BSS #%ld\n",*(undefined4 *)(iVar1 + 0x211e44));
      }
      *(int *)(iVar1 + 0x211e44) = *(int *)(iVar1 + 0x211e44) + 1;
      IterateOnBssTab2(uVar3,*(undefined4 *)((int)param_1 + 0x92c));
    }
    return;
  }
  printk(&_LC1,0x65e);
  dump_stack();
  return;
}

