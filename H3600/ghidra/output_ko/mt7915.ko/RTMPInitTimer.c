// module: mt7915.ko
// function: RTMPInitTimer @ 0x13c428
// size: 196 bytes
//

void RTMPInitTimer(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5)

{
  undefined4 unaff_lr;
  
  *(int *)(param_2 + 0x2c) = param_1 + 0xa7bf0c;
  _raw_spin_lock_bh(param_1 + 0xa7bf0c);
  RTMP_TimerListAdd(param_1,param_2);
  *(undefined1 *)(param_2 + 0x1e) = param_5;
  *(undefined4 *)(param_2 + 0x24) = param_4;
  *(undefined1 *)(param_2 + 0x1c) = 1;
  *(undefined1 *)(param_2 + 0x1d) = 0;
  *(int *)(param_2 + 0x28) = param_1;
  *(undefined4 *)(param_2 + 0x30) = unaff_lr;
  RTMP_OS_Init_Timer(param_1,param_2,param_3,param_2,param_1 + 0xa78448);
  if (3 < DebugLevel) {
    printk("%s: %lx\n","RTMPInitTimer",param_2);
  }
  _raw_spin_unlock_bh(*(undefined4 *)(param_2 + 0x2c));
  return;
}

