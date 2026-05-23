// module: mt7915.ko
// function: EventTxPowerShowInfo @ 0x1a8008
// size: 72 bytes
//

void EventTxPowerShowInfo(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 0) {
    return;
  }
  if (*(code **)(iVar1 + 0x2ec) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001a804c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x2ec))(param_1,param_2,param_3);
  return;
}

