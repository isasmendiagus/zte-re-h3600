// module: mt7915.ko
// function: HQA_SetPrimaryBW @ 0x26de1c
// size: 92 bytes
//

undefined4 HQA_SetPrimaryBW(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_SetPrimaryBW");
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

