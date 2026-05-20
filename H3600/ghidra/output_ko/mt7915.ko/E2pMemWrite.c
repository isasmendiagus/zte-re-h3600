// module: mt7915.ko
// function: E2pMemWrite @ 0x89228
// size: 72 bytes
//

void E2pMemWrite(int param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  
  if ((param_2 & 1) == 0) {
    param_4 = param_3 | param_4 << 8;
  }
  else {
    param_4 = param_4 | param_3 << 8;
  }
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xc) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0008926c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 0xc))(param_1,param_2,param_4);
    return;
  }
  return;
}

