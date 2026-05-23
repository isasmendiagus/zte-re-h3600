// module: mt7915.ko
// function: asic_trans_rxd_into_rxblk @ 0x1360c8
// size: 84 bytes
//

undefined4 asic_trans_rxd_into_rxblk(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1a0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00136108. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x1a0))(param_1,param_2,param_3);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"asic_trans_rxd_into_rxblk");
  return 0;
}

