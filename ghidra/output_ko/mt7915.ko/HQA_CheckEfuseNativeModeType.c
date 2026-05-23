// module: mt7915.ko
// function: HQA_CheckEfuseNativeModeType @ 0x26d3ac
// size: 144 bytes
//

undefined4 HQA_CheckEfuseNativeModeType(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  
  if (DebugLevel < 3) {
    bVar1 = "cp_support_is_enabled"[param_1 + 4];
  }
  else {
    printk("%s: %x\n","HQA_CheckEfuseNativeModeType","cp_support_is_enabled"[param_1 + 4]);
    bVar1 = "cp_support_is_enabled"[param_1 + 4];
  }
  *(uint *)(param_3 + 0xe) = (uint)bVar1 << 0x18;
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

