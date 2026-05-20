// module: mt7915.ko
// function: mt_restart_fw @ 0x1c1d3c
// size: 36 bytes
//

undefined4 mt_restart_fw(int param_1)

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

