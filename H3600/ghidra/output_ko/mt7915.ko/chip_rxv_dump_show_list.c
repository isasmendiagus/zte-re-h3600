// module: mt7915.ko
// function: chip_rxv_dump_show_list @ 0x136c60
// size: 48 bytes
//

void chip_rxv_dump_show_list(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x240) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136c8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x240))(param_1);
  return;
}

