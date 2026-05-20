// module: mt7915.ko
// function: asic_dump_dmac_amsdu_info @ 0x136298
// size: 56 bytes
//

undefined4 asic_dump_dmac_amsdu_info(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1b8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001362c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x1b8))(param_1);
    return uVar2;
  }
  return 0;
}

