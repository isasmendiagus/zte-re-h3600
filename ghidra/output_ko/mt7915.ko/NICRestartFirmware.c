// module: mt7915.ko
// function: NICRestartFirmware @ 0x1c81e4
// size: 4 bytes
//

undefined4 NICRestartFirmware(int param_1)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0xa7852c) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001c1d54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0xa7852c))(param_1,0);
    return uVar1;
  }
  return 0;
}

