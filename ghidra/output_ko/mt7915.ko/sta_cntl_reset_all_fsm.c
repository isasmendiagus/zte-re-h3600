// module: mt7915.ko
// function: sta_cntl_reset_all_fsm @ 0x6ff74
// size: 136 bytes
//

void sta_cntl_reset_all_fsm(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_1 + 0x92c);
  iVar3 = *(int *)(iVar2 + 8);
  iVar1 = GetStaCfgByWdev(iVar3,iVar2);
  if (iVar1 != 0) {
    if (iVar3 == 0) {
      printk(&_LC5,0x82e);
      dump_stack();
    }
    cntl_fsm_reset(iVar2);
    auth_fsm_reset(iVar2);
    assoc_fsm_reset(iVar2);
    sync_fsm_reset(iVar3,iVar2);
    sta_ifdown_fsm_reset_complete(iVar1);
    return;
  }
  printk(&_LC1,0x82d);
  dump_stack();
  return;
}

