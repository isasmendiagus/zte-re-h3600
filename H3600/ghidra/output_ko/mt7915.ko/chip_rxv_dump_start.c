// module: mt7915.ko
// function: chip_rxv_dump_start @ 0x136b98
// size: 48 bytes
//

void chip_rxv_dump_start(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x230) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136bc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x230))(param_1);
  return;
}

