// module: mt7915.ko
// function: AndesGetSpinLock @ 0x1a4520
// size: 224 bytes
//

int AndesGetSpinLock(int param_1,int param_2)

{
  if (param_1 + 0x20 == param_2) {
    param_1 = param_1 + 0x1c;
  }
  else if (param_1 + 0x2c == param_2) {
    param_1 = param_1 + 0x28;
  }
  else if (param_1 + 0x38 == param_2) {
    param_1 = param_1 + 0x34;
  }
  else if (param_1 + 0x44 == param_2) {
    param_1 = param_1 + 0x40;
  }
  else if (param_1 + 0x50 == param_2) {
    param_1 = param_1 + 0x4c;
  }
  else if (param_1 + 0x5c == param_2) {
    param_1 = param_1 + 0x58;
  }
  else {
    if (((-1 < DebugLevel) && (printk("list pointer = %p\n"), -1 < DebugLevel)) &&
       (printk("txq = %p, rxq = %p, ackq = %p, kickq = %p, tx_doneq = %p, rx_doneq = %p\n",
               param_1 + 0x20,param_1 + 0x2c,param_1 + 0x38,param_1 + 0x44,param_1 + 0x50,
               param_1 + 0x5c), -1 < DebugLevel)) {
      printk("%s:illegal list\n","AndesGetSpinLock");
    }
    param_1 = 0;
  }
  return param_1;
}

