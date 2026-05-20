// module: mt7915.ko
// function: HQA_HIFTestSetStopLoopback @ 0x274404
// size: 124 bytes
//

undefined4
HQA_HIFTestSetStopLoopback(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (0 < DebugLevel) {
    printk(&_LC11,"HQA_HIFTestSetStopLoopback",param_3,DebugLevel,param_4);
  }
  if (*(char *)(param_1 + 0xa3baf9) != '\0') {
    LoopBack_Stop(param_1);
  }
  *(undefined1 *)(param_1 + 0xa3baf8) = 0;
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

