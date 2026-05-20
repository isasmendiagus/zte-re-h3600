// module: mt7915.ko
// function: AsicUpdateRtsThld @ 0x131e54
// size: 164 bytes
//

void AsicUpdateRtsThld(int param_1,undefined4 param_2,undefined1 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 == 2) {
    if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
      return;
    }
    if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
       ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
      return;
    }
    if (*(code **)(iVar1 + 0x18) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00131ee0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(iVar1 + 0x18))(param_1,param_2,param_3,param_4);
      return;
    }
  }
  AsicNotSupportFunc(param_1,"AsicUpdateRtsThld");
  return;
}

