// module: mt7915.ko
// function: AsicBbpInitFromEEPROM @ 0x136e6c
// size: 48 bytes
//

void AsicBbpInitFromEEPROM(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x50) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00136e98. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x50))(param_1);
  return;
}

