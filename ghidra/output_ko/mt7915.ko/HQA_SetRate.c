// module: mt7915.ko
// function: HQA_SetRate @ 0x26f8b4
// size: 144 bytes
//

undefined4 HQA_SetRate(int param_1,undefined4 param_2,int param_3)

{
  undefined1 uVar1;
  
  if (DebugLevel < 3) {
    uVar1 = (undefined1)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  }
  else {
    printk(&_LC11,"HQA_SetRate");
    uVar1 = (undefined1)((uint)*(undefined4 *)(param_3 + 0xc) >> 0x18);
  }
  *(undefined1 *)(param_1 + 0xa3ad6c) = uVar1;
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

