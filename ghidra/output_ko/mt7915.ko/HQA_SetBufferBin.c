// module: mt7915.ko
// function: HQA_SetBufferBin @ 0x26d97c
// size: 92 bytes
//

undefined4 HQA_SetBufferBin(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (0 < DebugLevel) {
    printk("%s not support this commmand, to disable cal-free merge use DisableCalFree in profile setting\n"
           ,"HQA_SetBufferBin");
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

