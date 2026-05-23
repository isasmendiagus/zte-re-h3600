// module: mt7915.ko
// function: chip_get_rx_stat_band @ 0x1368b8
// size: 80 bytes
//

undefined4
chip_get_rx_stat_band(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 600) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001368fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 600))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  return 0;
}

