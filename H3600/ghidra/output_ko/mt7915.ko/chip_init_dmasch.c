// module: mt7915.ko
// function: chip_init_dmasch @ 0x1374f4
// size: 56 bytes
//

undefined4 chip_init_dmasch(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1c4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00137520. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x1c4))(param_1);
    return uVar2;
  }
  return 0;
}

