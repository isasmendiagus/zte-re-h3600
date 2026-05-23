// module: mt7915.ko
// function: AsicDisableSync @ 0x132b1c
// size: 68 bytes
//

void AsicDisableSync(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x80) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00132b50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x80))(param_1,param_2);
    return;
  }
  AsicNotSupportFunc(param_1,"AsicDisableSync");
  return;
}

