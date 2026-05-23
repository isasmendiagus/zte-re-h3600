// module: mt7915.ko
// function: MlmeRestartStateMachine @ 0x12d368
// size: 500 bytes
//

void MlmeRestartStateMachine(int param_1,undefined4 param_2)

{
  int iVar1;
  int *extraout_r1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined1 uStack_2d;
  int local_2c [2];
  
  local_2c[0] = 0;
  iVar1 = GetStaCfgByWdev();
  if (2 < DebugLevel) {
    printk("MlmeRestartStateMachine\n");
  }
  iVar3 = param_1 + 0x7960f4;
  _raw_spin_lock_bh(iVar3);
  if (*(char *)(param_1 + 0x7960f0) != '\0') {
    _raw_spin_unlock_bh(iVar3);
    return;
  }
  *(undefined1 *)(param_1 + 0x7960f0) = 1;
  _raw_spin_unlock_bh(iVar3);
  while( true ) {
    _raw_spin_lock_bh(param_1 + 0x796104);
    iVar4 = *(int *)(param_1 + 0x7960f8);
    _raw_spin_unlock_bh(param_1 + 0x796104);
    piVar2 = local_2c;
    if (iVar4 == 0) break;
    iVar4 = MlmeDequeue(param_1 + 0x7960f8);
    if (iVar4 == 0) {
      if (-1 < DebugLevel) {
        printk("MlmeRestartStateMachine: MlmeQueue empty\n");
      }
    }
    else {
      *(undefined1 *)(local_2c[0] + 0x922) = 0;
      *(undefined4 *)(local_2c[0] + 0x908) = 0;
    }
  }
  if (*(char *)(param_1 + 0x286285) == '\0' && iVar1 != 0) {
    RTMPCancelTimer(iVar1 + 0x211eb4,&uStack_2d);
    RTMPCancelTimer(iVar1 + 0x211ee8,&uStack_2d);
    RTMPCancelTimer(BN_mod_sqr + iVar1,&uStack_2d);
    RTMPCancelTimer(iVar1 + 0x211e80,&uStack_2d);
    RTMPCancelTimer(iVar1 + 0x211e4c,&uStack_2d);
    piVar2 = extraout_r1;
  }
  hc_reset_radio(param_1,piVar2);
  cntl_fsm_reset(param_2);
  auth_fsm_reset(param_2);
  assoc_fsm_reset(param_2);
  sync_fsm_reset(param_1,param_2);
  if (*(char *)(param_1 + 0x286285) == '\0') {
    *(undefined4 *)(param_1 + 0x795bac) = 0;
  }
  _raw_spin_lock_bh(iVar3);
  *(undefined1 *)(param_1 + 0x7960f0) = 0;
  _raw_spin_unlock_bh(iVar3);
  return;
}

