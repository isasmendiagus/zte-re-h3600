// module: mt7915.ko
// function: chip_get_rssi @ 0x1367a8
// size: 64 bytes
//

void chip_get_rssi(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x2e8) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001367e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x2e8))(param_1,param_2,param_3);
  return;
}

