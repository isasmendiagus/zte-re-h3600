// module: mt7915.ko
// function: HQA_TXBFSoundingStop @ 0x272510
// size: 88 bytes
//

undefined4
HQA_TXBFSoundingStop(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  Set_Stop_Sounding_Proc(param_1,0,param_3,param_4,param_4);
  if (0 < DebugLevel) {
    printk(&_LC11,"HQA_TXBFSoundingStop");
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

