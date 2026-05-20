// module: mt7915.ko
// function: RTMPSetTimer @ 0x13c4f0
// size: 260 bytes
//

void RTMPSetTimer(int param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 0x2c) == 0) {
    return;
  }
  _raw_spin_lock_bh(*(int *)(param_1 + 0x2c));
  if (*(char *)(param_1 + 0x1c) == '\0') {
    if (-1 < DebugLevel) {
      printk("RTMPSetTimer failed, Timer hasn\'t been initialize! <caller: %pS>\n");
    }
  }
  else if ((*(uint *)(*(int *)(param_1 + 0x28) + 0xa39f84) & 0x140) == 0) {
    *(undefined4 *)(param_1 + 0x20) = param_2;
    *(undefined1 *)(param_1 + 0x1d) = 0;
    if (*(char *)(param_1 + 0x1e) == '\x01') {
      *(undefined1 *)(param_1 + 0x1f) = 1;
      RTMP_SetPeriodicTimer(param_1,param_2);
    }
    else {
      *(undefined1 *)(param_1 + 0x1f) = 0;
      RTMP_OS_Add_Timer(param_1,param_2);
    }
    if (3 < DebugLevel) {
      printk("%s: %lx\n","RTMPSetTimer",param_1);
    }
  }
  else if (-1 < DebugLevel) {
    printk("RTMPSetTimer failed, Halt in Progress!\n");
  }
  _raw_spin_unlock_bh(*(undefined4 *)(param_1 + 0x2c));
  return;
}

