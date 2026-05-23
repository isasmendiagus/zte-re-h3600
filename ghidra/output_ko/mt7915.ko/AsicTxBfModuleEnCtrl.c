// module: mt7915.ko
// function: AsicTxBfModuleEnCtrl @ 0x13722c
// size: 92 bytes
//

undefined4
AsicTxBfModuleEnCtrl(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x130) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00137274. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x130))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicTxBfModuleEnCtrl");
  return 0;
}

