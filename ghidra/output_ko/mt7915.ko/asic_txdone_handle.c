// module: mt7915.ko
// function: asic_txdone_handle @ 0x136120
// size: 72 bytes
//

undefined4 asic_txdone_handle(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1a4) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0013615c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x1a4))(param_1,param_2,param_3);
    return uVar2;
  }
  return 1;
}

