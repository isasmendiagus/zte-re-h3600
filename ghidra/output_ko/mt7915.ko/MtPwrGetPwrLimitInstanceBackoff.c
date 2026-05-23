// module: mt7915.ko
// function: MtPwrGetPwrLimitInstanceBackoff @ 0x15114c
// size: 192 bytes
//

undefined4
MtPwrGetPwrLimitInstanceBackoff(int param_1,undefined4 param_2,int *param_3,undefined4 param_4)

{
  switch(param_2) {
  case 0:
    *param_3 = param_1 + 0xa78634;
    return 0;
  case 1:
    *param_3 = param_1 + 0x285a96;
    return 0;
  case 2:
    *param_3 = param_1 + 0x285aa7;
    return 0;
  case 3:
    *param_3 = param_1 + 0x285acd;
    return 0;
  case 4:
    *param_3 = param_1 + 0x285abc;
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("%s: invalid instance for backoff !!\n","MtPwrGetPwrLimitInstanceBackoff",param_3,
           DebugLevel,param_4);
    return 1;
  }
  return 1;
}

