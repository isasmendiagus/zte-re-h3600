// module: mt7915.ko
// function: MtPwrGetPwrLimitInstance @ 0x151224
// size: 112 bytes
//

undefined4
MtPwrGetPwrLimitInstance(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    MtPwrGetPwrLimitInstanceSku(param_1,param_3,param_4);
    return 0;
  }
  if (param_2 != 1) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: invalid instance type !!\n","MtPwrGetPwrLimitInstance");
    return 1;
  }
  MtPwrGetPwrLimitInstanceBackoff(param_1,param_3,param_4);
  return 0;
}

