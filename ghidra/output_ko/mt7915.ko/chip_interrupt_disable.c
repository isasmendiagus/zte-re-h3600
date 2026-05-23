// module: mt7915.ko
// function: chip_interrupt_disable @ 0x1375a0
// size: 48 bytes
//

void chip_interrupt_disable(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1cc) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001375cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x1cc))(param_1);
  return;
}

