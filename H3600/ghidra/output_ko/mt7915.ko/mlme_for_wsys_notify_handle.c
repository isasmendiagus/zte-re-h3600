// module: mt7915.ko
// function: mlme_for_wsys_notify_handle @ 0x12d054
// size: 784 bytes
//

undefined4 mlme_for_wsys_notify_handle(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 auStack_58 [4];
  int local_54;
  int *local_50;
  int local_4c;
  undefined1 auStack_48 [12];
  int *local_3c [3];
  undefined4 ****local_30;
  undefined4 ****local_2c;
  
  local_54 = *param_3;
  iVar4 = *(int *)(param_1 + 0xc);
  if (2 < DebugLevel) {
    printk("%s(): event_id: %d, wdev=%d\n","mlme_for_wsys_notify_handle",param_2,
           *(undefined1 *)(local_54 + 0xc));
  }
  iVar2 = local_54;
  if (param_2 == 4) {
    if (((*(int *)(local_54 + 0x14) == 2) && (*(int *)(local_54 + 8) != 0)) &&
       (iVar4 = GetAssociatedAPByWdev(*(int *)(local_54 + 8),local_54), iVar4 != 0)) {
      set_bss_color_info(iVar2,*(undefined1 *)(iVar4 + 0x86),*(undefined1 *)(iVar4 + 0x84));
    }
    bss_color_timer_init(local_54);
    return 1;
  }
  if (param_2 == 5) {
    bss_color_timer_release(local_54);
    return 1;
  }
  if (param_2 != 1) {
    return 1;
  }
  iVar2 = iVar4 + 0x5d4;
  local_4c = iVar2;
  _raw_spin_lock_bh(iVar2);
  *(undefined1 *)(iVar4 + 0x5d1) = 1;
  _raw_spin_unlock_bh(iVar2);
  if (*(char *)(iVar4 + 0x5d0) == '\0') {
LAB_0012d254:
    iVar2 = 0;
    local_3c[0] = (int *)0x0;
    iVar3 = *(int *)(iVar4 + 0x5d8);
    _raw_spin_lock_bh(local_4c);
    if (0 < iVar3) {
      do {
        iVar5 = MlmeDequeue(iVar4 + 0x5d8,local_3c);
        if (iVar5 == 0) break;
        if (local_54 != local_3c[0][0x24b]) {
          local_50 = local_3c[0];
          _raw_spin_lock_bh(iVar4 + 0x5e4);
          iVar5 = *(int *)(iVar4 + 0x5e0);
          iVar1 = iVar5 + 1;
          if (*(char *)(iVar1 * 0x930 + iVar4 + 0x5da) == '\0') {
            *(int *)(iVar4 + 0x5e0) = iVar1;
            if (iVar1 == 0x100) {
              *(undefined4 *)(iVar4 + 0x5e0) = 0;
            }
            *(int *)(iVar4 + 0x5d8) = *(int *)(iVar4 + 0x5d8) + 1;
            os_move_mem((void *)(iVar5 * 0x930 + iVar4 + 0x5d8 + 0x10),local_50,0x930);
          }
          _raw_spin_unlock_bh(iVar4 + 0x5e4);
        }
        iVar2 = iVar2 + 1;
        *(undefined1 *)((int)local_3c[0] + 0x922) = 0;
        local_3c[0][0x242] = 0;
      } while (iVar3 != iVar2);
    }
    _raw_spin_unlock_bh(local_4c);
  }
  else {
    iVar2 = 10;
    local_50 = &DebugLevel;
    do {
      if ((*(uint *)(((uint)auStack_58 & 0xffffe000) + 4) & 0x1fff00) == 0) {
        iVar3 = 10;
        __init_waitqueue_head(auStack_48,"&_wait",&SsidIe);
        do {
          local_3c[0] = (int *)0x0;
          local_30 = &local_30;
          local_2c = &local_30;
          for (iVar5 = 1; iVar1 = prepare_to_wait_event(auStack_48,local_3c,1),
              iVar5 != 0 && iVar1 == 0; iVar5 = schedule_timeout(iVar5)) {
          }
          finish_wait(auStack_48,local_3c);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      else {
        RtmpusecDelay(100000);
      }
      if (*(char *)(iVar4 + 0x5d0) == '\0') goto LAB_0012d254;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (-1 < *local_50) {
      printk("mlme can\'t polling to idle, timeout\n");
    }
  }
  iVar2 = local_4c;
  _raw_spin_lock_bh(local_4c);
  *(undefined1 *)(iVar4 + 0x5d1) = 0;
  _raw_spin_unlock_bh(iVar2);
  return 1;
}

