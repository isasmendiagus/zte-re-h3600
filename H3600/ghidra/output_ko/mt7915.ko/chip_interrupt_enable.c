// module: mt7915.ko
// function: chip_interrupt_enable @ 0x137570
// size: 48 bytes
//

void chip_interrupt_enable(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1d0) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0013759c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x1d0))(param_1);
  return;
}

