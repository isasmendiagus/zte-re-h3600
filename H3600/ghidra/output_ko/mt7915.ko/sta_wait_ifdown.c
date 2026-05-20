// module: mt7915.ko
// function: sta_wait_ifdown @ 0x68a44
// size: 132 bytes
//

void sta_wait_ifdown(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = RTMPMsecsToJiffies(500);
  iVar2 = wait_for_completion_timeout(param_1 + 0x213234,uVar1);
  if (iVar2 != 0) {
    return;
  }
  uVar1 = *(undefined4 *)(param_1 + 8);
  if (-1 < DebugLevel) {
    printk("(%s) sta idx [%d] can\'t reset fsm within 500ms, do reset in main thread\n",
           "sta_wait_ifdown",*(undefined1 *)(param_1 + 0xe));
  }
  cntl_fsm_reset(param_1);
  auth_fsm_reset(param_1);
  assoc_fsm_reset(param_1);
  sync_fsm_cancel_req_action(uVar1,param_1);
  return;
}

