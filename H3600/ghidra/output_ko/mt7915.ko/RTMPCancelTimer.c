// module: mt7915.ko
// function: RTMPCancelTimer @ 0x13c5f8
// size: 188 bytes
//

void RTMPCancelTimer(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

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
      if (3 < DebugLevel) {
        printk("%s: %lx\n","RTMPCancelTimer",param_1);
      }
    }
    _raw_spin_unlock_bh(*(undefined4 *)(param_1 + 0x2c));
    return;
  }
  if (DebugLevel < 4) {
    return;
  }
  printk("RTMPCancelTimer failed, Timer hasn\'t been initialize!\n",param_2,param_3,param_4);
  return;
}

