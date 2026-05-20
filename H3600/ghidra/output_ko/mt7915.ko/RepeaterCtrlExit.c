// module: mt7915.ko
// function: RepeaterCtrlExit @ 0x838d4
// size: 496 bytes
//

void RepeaterCtrlExit(int param_1,int param_2)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_40 [12];
  undefined4 local_34 [3];
  undefined4 ****local_28;
  undefined4 ****local_24;
  
  repeater_disconnect_by_band();
  iVar3 = 0x3e9;
  do {
    while( true ) {
      if ((&DAT_00367912)[param_1 + param_2] == '\0') goto LAB_000839d0;
      if (0 < DebugLevel) {
        printk("%s, wait entry to be deleted\n","RepeaterCtrlExit");
      }
      if ((*(uint *)(((uint)auStack_40 & 0xffffe000) + 4) & 0x1fff00) != 0) break;
      __init_waitqueue_head(auStack_40,"&_wait",&g_u4TxBfOui);
      local_28 = &local_28;
      local_34[0] = 0;
      local_24 = local_28;
      for (iVar4 = 1; iVar1 = prepare_to_wait_event(auStack_40,local_34,1), iVar4 != 0 && iVar1 == 0
          ; iVar4 = schedule_timeout(iVar4)) {
      }
      finish_wait(auStack_40,local_34);
      iVar3 = iVar3 + -1;
      if (iVar3 == 0) goto LAB_000839d0;
    }
    RtmpusecDelay(10000);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
LAB_000839d0:
  puVar2 = &DAT_00367914 + param_1;
  _raw_spin_lock_bh(puVar2);
  if (((&DAT_0036790d)[param_1] != '\0') &&
     ((&DAT_0036790f)[param_1] == '\0' && (&DAT_0036790e)[param_1] == '\0')) {
    (&DAT_0036790d)[param_1] = 0;
    if (*(int *)(&DAT_003687ac + param_1) != 0) {
      os_free_mem();
      *(undefined4 *)(&DAT_003687ac + param_1) = 0;
    }
    if (*(int *)(&DAT_003687a8 + param_1) != 0) {
      os_free_mem();
      *(undefined4 *)(&DAT_003687a8 + param_1) = 0;
    }
    if (0 < DebugLevel) {
      printk("%s() is done\n","RepeaterCtrlExit");
    }
    _raw_spin_unlock_bh(puVar2);
    return;
  }
  _raw_spin_unlock_bh(puVar2);
  if (1 < DebugLevel) {
    printk("%s, wrong state(%d,%d)\n","RepeaterCtrlExit",(&DAT_0036790d)[param_1],
           (&DAT_0036790f)[param_1] | (&DAT_0036790e)[param_1]);
  }
  return;
}

