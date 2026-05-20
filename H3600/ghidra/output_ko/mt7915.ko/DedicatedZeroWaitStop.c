// module: mt7915.ko
// function: DedicatedZeroWaitStop @ 0x22ec28
// size: 108 bytes
//

void DedicatedZeroWaitStop(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(param_1 + 0x7953fa) != '\x01') {
    return;
  }
  if (*(int *)(param_1 + 0xa79184) != 2) {
    return;
  }
  *(undefined4 *)(param_1 + 0xa79184) = 0;
  DfsDedicatedOutBandRDDStop(param_1);
  if (*(code **)(iVar1 + 0x280) == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0022ec90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x280))(param_1,8,1);
  return;
}

