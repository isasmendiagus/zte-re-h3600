// module: mt7915.ko
// function: HQA_UDMAAction @ 0x26d340
// size: 104 bytes
//

undefined4 HQA_UDMAAction(undefined4 param_1,undefined4 param_2,int param_3)

{
  if (0 < DebugLevel) {
    printk(&_LC11,"HQA_UDMAAction");
  }
  *(undefined4 *)(param_3 + 0xe) = 0;
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

