// module: mt7915.ko
// function: asic_write_txp_info @ 0x135e94
// size: 80 bytes
//

undefined4 asic_write_txp_info(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x170) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00135ed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x170))(param_1,param_2,param_3);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"asic_write_txp_info");
  return 1;
}

