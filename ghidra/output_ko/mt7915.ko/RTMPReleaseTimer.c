// module: mt7915.ko
// function: RTMPReleaseTimer @ 0x13c79c
// size: 220 bytes
//

void RTMPReleaseTimer(int param_1,char *param_2)

{
  if (*(int *)(param_1 + 0x2c) != 0) {
    _raw_spin_lock_bh(*(int *)(param_1 + 0x2c));
    if (*(char *)(param_1 + 0x1c) != '\0') {
      if (*(char *)(param_1 + 0x1d) == '\0') {
        *(undefined1 *)(param_1 + 0x1f) = 0;
      }
      _raw_spin_unlock_bh(*(undefined4 *)(param_1 + 0x2c));
      RTMP_OS_Del_Timer(param_1,param_2);
      _raw_spin_lock_bh(*(undefined4 *)(param_1 + 0x2c));
      if (*param_2 == '\x01') {
        *(undefined1 *)(param_1 + 0x1d) = 1;
      }
      RTMP_OS_Release_Timer(param_1);
      *(undefined1 *)(param_1 + 0x1c) = 0;
      RTMP_TimerListRelease(*(undefined4 *)(param_1 + 0x28),param_1);
      if (3 < DebugLevel) {
        printk("%s: %lx\n","RTMPReleaseTimer",param_1);
      }
    }
    _raw_spin_unlock_bh(*(undefined4 *)(param_1 + 0x2c));
  }
  if (DebugLevel < 4) {
    return;
  }
  printk("RTMPReleasefailed, Timer hasn\'t been initialize!\n");
  return;
}

