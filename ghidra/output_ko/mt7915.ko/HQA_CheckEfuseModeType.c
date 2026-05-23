// module: mt7915.ko
// function: HQA_CheckEfuseModeType @ 0x26d440
// size: 144 bytes
//

undefined4 HQA_CheckEfuseModeType(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  
  if (DebugLevel < 3) {
    bVar1 = "cp_support_is_enabled"[param_1 + 5];
  }
  else {
    printk("%s: %x\n","HQA_CheckEfuseModeType","cp_support_is_enabled"[param_1 + 5]);
    bVar1 = "cp_support_is_enabled"[param_1 + 5];
  }
  *(uint *)(param_3 + 0xe) = (uint)bVar1 << 0x18;
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

