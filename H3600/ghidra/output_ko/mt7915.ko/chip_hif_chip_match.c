// module: mt7915.ko
// function: chip_hif_chip_match @ 0x137680
// size: 36 bytes
//

void chip_hif_chip_match(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops();
  if (*(code **)(iVar1 + 0x28c) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001376a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x28c))(param_1);
  return;
}

