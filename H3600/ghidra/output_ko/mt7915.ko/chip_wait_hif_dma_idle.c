// module: mt7915.ko
// function: chip_wait_hif_dma_idle @ 0x13746c
// size: 80 bytes
//

undefined4
chip_wait_hif_dma_idle(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 500) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001374b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 500))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  return 0;
}

