// module: mt7915.ko
// function: chip_set_hif_dma @ 0x137424
// size: 72 bytes
//

undefined4 chip_set_hif_dma(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1f0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00137460. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x1f0))(param_1,param_2,param_3);
    return uVar2;
  }
  return 0;
}

