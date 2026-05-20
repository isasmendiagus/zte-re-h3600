// module: mt7915.ko
// function: EventTxPowerAllRatePowerShowInfo @ 0x1a8050
// size: 72 bytes
//

void EventTxPowerAllRatePowerShowInfo(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 == 0) {
    return;
  }
  if (*(code **)(iVar1 + 0x20c) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x001a8094. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x20c))(param_1,param_2,param_3);
  return;
}

