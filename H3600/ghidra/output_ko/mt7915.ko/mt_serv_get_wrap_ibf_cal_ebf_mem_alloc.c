// module: mt7915.ko
// function: mt_serv_get_wrap_ibf_cal_ebf_mem_alloc @ 0x252ce4
// size: 36 bytes
//

undefined4 mt_serv_get_wrap_ibf_cal_ebf_mem_alloc(undefined4 *param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1[0x7c4] + 0x1b8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00252cfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1[0x7c4] + 0x1b8))(*param_1);
    return uVar1;
  }
  return 0x100;
}

