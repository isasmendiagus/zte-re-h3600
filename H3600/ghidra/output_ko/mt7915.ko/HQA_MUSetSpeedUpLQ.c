// module: mt7915.ko
// function: HQA_MUSetSpeedUpLQ @ 0x272108
// size: 132 bytes
//

undefined4 HQA_MUSetSpeedUpLQ(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  uVar2 = hqa_wifi_test_mu_speed_up_lq(param_1,uVar1);
  if (0 < DebugLevel) {
    printk("%s: spdup_lq:%x\n","HQA_MUSetSpeedUpLQ",uVar1);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar2);
  return uVar2;
}

