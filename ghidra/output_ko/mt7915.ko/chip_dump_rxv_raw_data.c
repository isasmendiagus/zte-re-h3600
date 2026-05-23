// module: mt7915.ko
// function: chip_dump_rxv_raw_data @ 0x136ab8
// size: 56 bytes
//

void chip_dump_rxv_raw_data(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x210) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136aec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x210))(param_1,param_2);
  return;
}

