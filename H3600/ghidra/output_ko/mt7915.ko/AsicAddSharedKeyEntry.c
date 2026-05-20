// module: mt7915.ko
// function: AsicAddSharedKeyEntry @ 0x133684
// size: 84 bytes
//

void AsicAddSharedKeyEntry(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xb4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001336c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0xb4))(param_1,param_2,param_3,param_4);
    return;
  }
  AsicNotSupportFunc(param_1,"AsicAddSharedKeyEntry");
  return;
}

