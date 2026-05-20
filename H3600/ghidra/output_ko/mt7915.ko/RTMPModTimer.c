// module: mt7915.ko
// function: RTMPModTimer @ 0x13c6b8
// size: 224 bytes
//

void RTMPModTimer(int param_1,undefined4 param_2)

{
  undefined1 auStack_11 [5];
  
  if (*(int *)(param_1 + 0x2c) == 0) {
    return;
  }
  _raw_spin_lock_bh(*(int *)(param_1 + 0x2c));
  if (*(char *)(param_1 + 0x1c) == '\0') {
    if (-1 < DebugLevel) {
      printk("RTMPModTimer failed, Timer hasn\'t been initialize!\n");
    }
    _raw_spin_unlock_bh(*(undefined4 *)(param_1 + 0x2c));
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = param_2;
    *(undefined1 *)(param_1 + 0x1d) = 0;
    if (*(char *)(param_1 + 0x1e) == '\x01') {
      _raw_spin_unlock_bh(*(undefined4 *)(param_1 + 0x2c));
      RTMPCancelTimer(param_1,auStack_11);
      RTMPSetTimer(param_1,param_2);
    }
    else {
      RTMP_OS_Mod_Timer(param_1,param_2);
      _raw_spin_unlock_bh(*(undefined4 *)(param_1 + 0x2c));
    }
    if (3 < DebugLevel) {
      printk("%s: %lx\n","RTMPModTimer",param_1);
    }
  }
  return;
}

