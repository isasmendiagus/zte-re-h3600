// module: mt7915.ko
// function: asic_dump_rxinfo @ 0x1361e8
// size: 56 bytes
//

void asic_dump_rxinfo(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x1b0) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0013621c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x1b0))(param_1,param_2);
  return;
}

