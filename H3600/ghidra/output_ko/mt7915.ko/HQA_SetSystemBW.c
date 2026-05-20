// module: mt7915.ko
// function: HQA_SetSystemBW @ 0x26f830
// size: 128 bytes
//

undefined4 HQA_SetSystemBW(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  if (2 < DebugLevel) {
    printk("%s: BW = %d\n","HQA_SetSystemBW",
           uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18
          );
  }
  *(char *)(param_1 + 0xa3ad65) = (char)(uVar1 >> 0x18);
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

