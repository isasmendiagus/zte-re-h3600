// module: mt7915.ko
// function: AsicEnableIbssSync @ 0x132bbc
// size: 84 bytes
//

void AsicEnableIbssSync(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x88) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00132c00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x88))(param_1,param_2,param_3,param_4);
    return;
  }
  AsicNotSupportFunc(param_1,"AsicEnableIbssSync");
  return;
}

