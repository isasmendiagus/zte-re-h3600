// module: mt7915.ko
// function: HQA_GetFreeEfuseBlock @ 0x2754b0
// size: 144 bytes
//

undefined4 HQA_GetFreeEfuseBlock(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint local_1c [2];
  
  if (DebugLevel < 3) {
    eFuseGetFreeBlockCount(param_1,local_1c);
  }
  else {
    printk(&_LC11,"HQA_GetFreeEfuseBlock");
    eFuseGetFreeBlockCount(param_1,local_1c);
  }
  local_1c[0] = local_1c[0] << 0x18 | (local_1c[0] >> 8 & 0xff) << 0x10 |
                (local_1c[0] >> 0x10 & 0xff) << 8 | local_1c[0] >> 0x18;
  *(uint *)(param_3 + 0xe) = local_1c[0];
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

