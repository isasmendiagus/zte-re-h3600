// module: mt7915.ko
// function: get_low_mid_hi_index @ 0x1456f4
// size: 280 bytes
//

undefined4
get_low_mid_hi_index(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 < 0xf) {
    if (param_1 - 1 < 5) {
      return 0;
    }
    if (param_1 - 6 < 5) {
      return 1;
    }
    if (param_1 - 0xb < 4) {
      return 2;
    }
  }
  else {
    if ((param_1 + 0x48 & 0xff) < 5) {
      return 0;
    }
    if ((param_1 + 0x40 & 0xff) < 5) {
      return 1;
    }
    if (param_1 - 0x24 < 7) {
      return 0;
    }
    if (param_1 - 0x2c < 5) {
      return 1;
    }
    if (param_1 - 0x34 < 5) {
      return 0;
    }
    if (param_1 - 0x3a < 7) {
      return 1;
    }
    if (param_1 - 0x62 < 7) {
      return 0;
    }
    if (param_1 - 0x6a < 9) {
      return 1;
    }
    if (param_1 - 0x74 < 0xd) {
      return 0;
    }
    if ((param_1 + 0x7e & 0xff) < 0xf) {
      return 1;
    }
    if ((param_1 + 0x6b & 0xff) < 8) {
      return 0;
    }
    if ((param_1 + 99 & 0xff) < 9) {
      return 1;
    }
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("illegal channel(%d)\n",param_1,param_3,DebugLevel,param_4);
  return 0;
}

