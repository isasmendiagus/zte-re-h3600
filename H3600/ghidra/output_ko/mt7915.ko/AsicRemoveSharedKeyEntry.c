// module: mt7915.ko
// function: AsicRemoveSharedKeyEntry @ 0x1336dc
// size: 92 bytes
//

void AsicRemoveSharedKeyEntry(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 != 2) {
    AsicNotSupportFunc(param_1,"AsicRemoveSharedKeyEntry");
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00133734. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0xb8))(param_1,param_2,param_3);
  return;
}

