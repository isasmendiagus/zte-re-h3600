// module: mt7915.ko
// function: HQA_MUSetEnable @ 0x271e48
// size: 132 bytes
//

undefined4 HQA_MUSetEnable(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = hqa_wifi_test_mu_set_enable(param_1,uVar1 >> 0x18);
  if (0 < DebugLevel) {
    printk("%s: MU is_enable:%x\n","HQA_MUSetEnable",
           uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18
          );
  }
  FUN_0026cdd0(param_3,param_2,2,uVar2);
  return uVar2;
}

