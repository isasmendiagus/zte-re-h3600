// module: mt7915.ko
// function: BndStrg_CheckConnectionReq @ 0x9cac4
// size: 64 bytes
//

undefined4 BndStrg_CheckConnectionReq(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (((param_2 != 0) && (*(int *)(param_2 + 0x1018) != 0)) && (*(char *)(param_2 + 5) == '\x01')) {
                    /* WARNING: Could not recover jumptable at 0x0009cb00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(int *)(param_2 + 0x1018) + 0x18))();
    return uVar1;
  }
  return 1;
}

