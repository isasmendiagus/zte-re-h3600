// module: mt7915.ko
// function: ate_set_manual_assoc @ 0xe92c0
// size: 56 bytes
//

void ate_set_manual_assoc(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x178) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000e92f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x178))(param_1,param_2);
  return;
}

