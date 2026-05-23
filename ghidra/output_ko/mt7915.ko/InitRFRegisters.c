// module: mt7915.ko
// function: InitRFRegisters @ 0x1c8354
// size: 96 bytes
//

void InitRFRegisters(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s(): Init RF Registers\n","InitRFRegisters");
  }
  if (*(code **)(iVar1 + 0x28) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001c8398. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x28))(param_1);
  return;
}

