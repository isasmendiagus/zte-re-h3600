// module: mt7915.ko
// function: MtPwrGetPwrLimitInstanceSku @ 0x151074
// size: 192 bytes
//

undefined4
MtPwrGetPwrLimitInstanceSku(int param_1,undefined4 param_2,int *param_3,undefined4 param_4)

{
  switch(param_2) {
  case 0:
    *param_3 = param_1 + 0xa7862c;
    return 0;
  case 1:
    *param_3 = param_1 + 0x285a5e;
    return 0;
  case 2:
    *param_3 = param_1 + 0x285a6b;
    return 0;
  case 3:
    *param_3 = param_1 + 0x285a87;
    return 0;
  case 4:
    *param_3 = param_1 + 0x285a7a;
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("%s: invalid instance for sku !!\n","MtPwrGetPwrLimitInstanceSku",param_3,DebugLevel,
           param_4);
    return 1;
  }
  return 1;
}

