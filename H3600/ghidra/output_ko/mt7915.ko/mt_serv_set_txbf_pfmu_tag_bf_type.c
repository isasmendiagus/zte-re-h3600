// module: mt7915.ko
// function: mt_serv_set_txbf_pfmu_tag_bf_type @ 0x252c50
// size: 40 bytes
//

undefined4 mt_serv_set_txbf_pfmu_tag_bf_type(undefined4 *param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1[0x7c4] + 0x1a4) != 0) {
                    /* WARNING: Could not recover jumptable at 0x00252c6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1[0x7c4] + 0x1a8))(*param_1);
    return uVar1;
  }
  return 0x100;
}

