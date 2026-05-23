// module: mt7915.ko
// function: MT_ATESetTxTonePower @ 0x27f700
// size: 60 bytes
//

undefined4
MT_ATESetTxTonePower(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (2 < DebugLevel) {
    printk("%s: pwr1:%d, pwr2:%d\n","MT_ATESetTxTonePower",param_2,param_3,param_4);
  }
  return 0;
}

