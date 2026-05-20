// module: mt7915.ko
// function: mt_serv_set_txbf_pfmu_tag_rmsd_thrd @ 0x252de0
// size: 36 bytes
//

undefined4 mt_serv_set_txbf_pfmu_tag_rmsd_thrd(undefined4 *param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1[0x7c4] + 0x1d0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00252df8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1[0x7c4] + 0x1d0))(*param_1);
    return uVar1;
  }
  return 0x100;
}

