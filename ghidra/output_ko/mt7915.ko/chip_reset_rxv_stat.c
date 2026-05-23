// module: mt7915.ko
// function: chip_reset_rxv_stat @ 0x136af0
// size: 56 bytes
//

void chip_reset_rxv_stat(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x214) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136b24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x214))(param_1,param_2);
  return;
}

