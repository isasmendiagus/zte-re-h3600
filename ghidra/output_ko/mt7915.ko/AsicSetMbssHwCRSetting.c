// module: mt7915.ko
// function: AsicSetMbssHwCRSetting @ 0x13458c
// size: 76 bytes
//

void AsicSetMbssHwCRSetting(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x124) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001345c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x124))(param_1,param_2,param_3);
    return;
  }
  AsicNotSupportFunc(param_1,"AsicSetMbssHwCRSetting");
  return;
}

