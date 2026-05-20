// module: mt7915.ko
// function: chip_dump_ser_stat @ 0x137714
// size: 56 bytes
//

void chip_dump_ser_stat(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x298) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00137748. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x298))(param_1,param_2);
  return;
}

