// module: mt7915.ko
// function: chip_fw_init @ 0x136760
// size: 72 bytes
//

void chip_fw_init(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(int *)(iVar1 + 0xb0) == 0) {
    return;
  }
  iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar2 != 2) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001367a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0xb0))(param_1);
  return;
}

