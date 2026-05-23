// module: mt7915.ko
// function: mt_serv_set_ibf_phase_cal_e2p_update @ 0x252b14
// size: 36 bytes
//

undefined4 mt_serv_set_ibf_phase_cal_e2p_update(undefined4 *param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1[0x7c4] + 0x194) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00252b2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1[0x7c4] + 0x194))(*param_1);
    return uVar1;
  }
  return 0x205;
}

