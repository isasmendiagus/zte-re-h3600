// module: mt7915.ko
// function: mtf_calculate_ecc @ 0x1a1098
// size: 108 bytes
//

void mtf_calculate_ecc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (-1 < DebugLevel) {
    printk("%s: oper:%d, group:%d\n","mtf_calculate_ecc",param_2,param_3);
  }
  cmd_calculate_ecc(param_1,param_2,param_3,param_4);
  return;
}

