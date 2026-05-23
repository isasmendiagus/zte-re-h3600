// module: mt7915.ko
// function: mt_serv_set_txbf_pfmu_tag_se_idx @ 0x252db8
// size: 40 bytes
//

undefined4 mt_serv_set_txbf_pfmu_tag_se_idx(undefined4 *param_1,undefined1 param_2)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1[0x7c4] + 0x1cc) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00252dd4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1[0x7c4] + 0x1cc))(*param_1,param_2);
    return uVar1;
  }
  return 0x100;
}

