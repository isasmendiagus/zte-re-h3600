// module: mt7915.ko
// function: asic_txbf_bfee_adaption @ 0x1372dc
// size: 68 bytes
//

undefined4 asic_txbf_bfee_adaption(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x138) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0013730c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x138))();
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"asic_txbf_bfee_adaption");
  return 0;
}

