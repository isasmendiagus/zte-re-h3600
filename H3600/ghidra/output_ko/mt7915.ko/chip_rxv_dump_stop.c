// module: mt7915.ko
// function: chip_rxv_dump_stop @ 0x136bc8
// size: 48 bytes
//

void chip_rxv_dump_stop(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x234) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136bf4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x234))(param_1);
  return;
}

