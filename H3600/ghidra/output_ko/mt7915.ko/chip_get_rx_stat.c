// module: mt7915.ko
// function: chip_get_rx_stat @ 0x1369f8
// size: 64 bytes
//

void chip_get_rx_stat(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x250) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136a34. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x250))(param_1,param_2,param_3);
  return;
}

