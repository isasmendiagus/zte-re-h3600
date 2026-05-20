// module: mt7915.ko
// function: chip_sw_int_handler @ 0x137648
// size: 56 bytes
//

void chip_sw_int_handler(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1dc) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0013767c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x1dc))(param_1,param_2);
  return;
}

