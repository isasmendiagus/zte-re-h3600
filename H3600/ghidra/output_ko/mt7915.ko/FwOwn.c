// module: mt7915.ko
// function: FwOwn @ 0x19b374
// size: 56 bytes
//

void FwOwn(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 0) {
    return;
  }
  if (*(code **)(iVar1 + 0x270) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0019b3a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x270))(param_1);
  return;
}

