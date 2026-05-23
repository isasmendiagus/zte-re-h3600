// module: mt7915.ko
// function: HQA_GetChipID @ 0x26e3f8
// size: 136 bytes
//

undefined4 HQA_GetChipID(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  if (DebugLevel < 3) {
    uVar1 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc);
  }
  else {
    printk(&_LC11,"HQA_GetChipID");
    uVar1 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc);
  }
  *(uint *)(param_3 + 0xe) =
       uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

