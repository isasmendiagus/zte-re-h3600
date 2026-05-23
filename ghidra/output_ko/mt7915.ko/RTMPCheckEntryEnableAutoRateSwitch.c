// module: mt7915.ko
// function: RTMPCheckEntryEnableAutoRateSwitch @ 0x130a44
// size: 204 bytes
//

undefined1
RTMPCheckEntryEnableAutoRateSwitch(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  
  if (param_2 == (int *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
  }
  else {
    if (param_2[2] != 0) {
      if (*(char *)(param_1 + 0x286285) == '\x01') {
        uVar1 = *(undefined1 *)(param_2[2] + 0x8b0);
      }
      else if (*(char *)(param_1 + 0x286285) == '\0') {
        uVar1 = 0;
        if ((*param_2 == 0x20001) && (param_2[0x3f] == 2)) {
          uVar1 = (&DAT_0036e408)[param_1];
        }
      }
      else {
        uVar1 = 1;
      }
      return uVar1;
    }
    if (DebugLevel < 0) {
      return 0;
    }
  }
  printk("%s(): entry(%p) or wdev(%p) is NULL!\n","RTMPCheckEntryEnableAutoRateSwitch",param_2,0,
         param_4);
  return 0;
}

