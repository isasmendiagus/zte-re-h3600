// module: mt7915.ko
// function: asic_get_bcn_tx_cnt @ 0x1364e4
// size: 72 bytes
//

undefined4 asic_get_bcn_tx_cnt(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x210) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00136518. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x210))(param_1,param_2);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"asic_get_bcn_tx_cnt");
  return 1;
}

