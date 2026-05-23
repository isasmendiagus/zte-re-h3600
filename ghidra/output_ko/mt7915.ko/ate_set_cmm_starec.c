// module: mt7915.ko
// function: ate_set_cmm_starec @ 0xe92f8
// size: 56 bytes
//

void ate_set_cmm_starec(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x17c) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000e932c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x17c))(param_1,param_2);
  return;
}

