// module: mt7915.ko
// function: chip_reset_hif_dma @ 0x1374bc
// size: 56 bytes
//

undefined4 chip_reset_hif_dma(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1f8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001374e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x1f8))(param_1);
    return uVar2;
  }
  return 0;
}

