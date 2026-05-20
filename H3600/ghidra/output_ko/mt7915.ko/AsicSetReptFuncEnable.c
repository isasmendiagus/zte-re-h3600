// module: mt7915.ko
// function: AsicSetReptFuncEnable @ 0x132584
// size: 272 bytes
//

undefined4 AsicSetReptFuncEnable(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("%s, caller:%pS\n","AsicSetReptFuncEnable");
  }
  repeater_set_enable(param_1,param_2,param_3);
  if (*(int *)(iVar1 + 0x50) != 0) {
    if (param_2 == 0) {
      RepeaterCtrlExit(param_1,param_3);
    }
    else {
      RepeaterCtrlInit();
    }
    if (0 < DebugLevel) {
      uVar2 = repeater_get_enable(param_1,param_3);
      uVar3 = repeater_enable_by_any_band(param_1);
      printk("Band_%d_RpEn(%d),RpEnByAnyBnd(%d),RpEn(%d)\n",param_3,uVar2,uVar3,
             (&DAT_0036790d)[param_1]);
    }
                    /* WARNING: Could not recover jumptable at 0x00132618. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x50))(param_1,param_2,param_3);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicSetReptFuncEnable");
  return 0;
}

