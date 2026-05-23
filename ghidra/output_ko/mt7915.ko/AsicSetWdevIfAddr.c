// module: mt7915.ko
// function: AsicSetWdevIfAddr @ 0x13453c
// size: 76 bytes
//

void AsicSetWdevIfAddr(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x120) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00134578. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0x120))(param_1,param_2,param_3);
    return;
  }
  AsicNotSupportFunc(param_1,"AsicSetWdevIfAddr");
  return;
}

