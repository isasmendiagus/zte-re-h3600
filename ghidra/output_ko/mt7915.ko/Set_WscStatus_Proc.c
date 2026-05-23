// module: mt7915.ko
// function: Set_WscStatus_Proc @ 0x27a6c
// size: 80 bytes
//

undefined4 Set_WscStatus_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  if (2 < DebugLevel) {
    uVar1 = *(uint *)(*param_1 + 0x3c) & 0xff;
    printk("IF(ra%d) Set_WscStatus_Proc::(WscStatus=%d)\n",uVar1,param_1[uVar1 * 0x160d + 0xae14e],
           param_1 + uVar1 * 0x160d + 0xae000,param_4);
  }
  return 1;
}

