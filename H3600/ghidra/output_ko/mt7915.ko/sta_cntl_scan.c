// module: mt7915.ko
// function: sta_cntl_scan @ 0x70200
// size: 248 bytes
//

void sta_cntl_scan(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x92c);
  iVar2 = *(int *)(iVar3 + 8);
  get_scan_tab_by_wdev(iVar2,iVar3);
  if (iVar2 == 0) {
    printk(&_LC5,0x760);
    dump_stack();
  }
  iVar1 = GetStaCfgByWdev(iVar2,iVar3);
  if (iVar1 != 0) {
    if ((*(uint *)(iVar2 + 0xa3ac14) & 1) == 0) {
      if ((*(int *)(iVar2 + 0xa77bb4) != 1) ||
         ((*(uint *)(*(int *)(iVar2 + 0xa77bb8) + 0x4e0) & 1) == 0)) {
        sync_cntl_fsm_to_idle_when_scan_req(iVar2,iVar3);
        MlmeEnqueueWithWdev(iVar2,4,2,*(undefined4 *)(param_1 + 0x908),param_1,0,iVar3);
        cntl_fsm_state_transition(iVar3,1,"sta_cntl_scan");
        return;
      }
    }
    return;
  }
  printk(&_LC1,0x761);
  dump_stack();
  return;
}

