// module: mt7915.ko
// function: HQA_GetRxSNR @ 0x26e53c
// size: 168 bytes
//

undefined4 HQA_GetRxSNR(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  if (DebugLevel < 3) {
    uVar1 = *(uint *)(param_1 + 0xa3b794);
  }
  else {
    printk(&_LC11,"HQA_GetRxSNR");
    uVar1 = *(uint *)(param_1 + 0xa3b794);
  }
  *(uint *)(param_3 + 0xe) =
       uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar1 = *(uint *)(param_1 + 0xa3b798);
  *(uint *)(param_3 + 0x12) =
       uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  FUN_0026cdd0(param_3,param_2,10,0);
  return 0;
}

