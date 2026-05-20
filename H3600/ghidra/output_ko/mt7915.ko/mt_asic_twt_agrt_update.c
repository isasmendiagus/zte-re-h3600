// module: mt7915.ko
// function: mt_asic_twt_agrt_update @ 0x19b0b0
// size: 228 bytes
//

void mt_asic_twt_agrt_update
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 8);
  iVar2 = hc_get_chip_ops(*(undefined4 *)(iVar4 + 0xa797a0));
  iVar3 = wlan_config_get_asic_twt_caps(param_1);
  if (iVar3 == 0) {
    if (2 < DebugLevel) {
      uVar1 = 0xb3c;
LAB_0019b184:
      printk(uVar1 | 0x300000,"mt_asic_twt_agrt_update");
      return;
    }
  }
  else {
    if (*(code **)(iVar2 + 0x48) != (code *)0x0) {
      (**(code **)(iVar2 + 0x48))
                (iVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12);
      return;
    }
    if (2 < DebugLevel) {
      uVar1 = 0xb58;
      goto LAB_0019b184;
    }
  }
  return;
}

