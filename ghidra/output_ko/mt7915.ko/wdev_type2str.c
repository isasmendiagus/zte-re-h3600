// module: mt7915.ko
// function: wdev_type2str @ 0xe19d8
// size: 308 bytes
//

undefined4 wdev_type2str(int param_1)

{
  if (param_1 == 0x40) {
    return wdev_type_str._24_4_;
  }
  if (param_1 < 0x41) {
    if (param_1 == 4) {
      return wdev_type_str._8_4_;
    }
    if (param_1 < 5) {
      if (param_1 == 1) {
        return wdev_type_str._0_4_;
      }
      if (param_1 == 2) {
        return wdev_type_str._4_4_;
      }
    }
    else {
      if (param_1 == 0x10) {
        return wdev_type_str._16_4_;
      }
      if (param_1 == 0x20) {
        return wdev_type_str._20_4_;
      }
      if (param_1 == 8) {
        return wdev_type_str._12_4_;
      }
    }
  }
  else {
    if (param_1 == 0x800) {
      return wdev_type_str._40_4_;
    }
    if (param_1 < 0x801) {
      if (param_1 == 0x100) {
        return wdev_type_str._32_4_;
      }
      if (param_1 == 0x200) {
        return wdev_type_str._36_4_;
      }
    }
    else {
      if ((param_1 == 0x2000) || (param_1 == 0x4000)) {
        return wdev_type_str._44_4_;
      }
      if (param_1 == 0x1000) {
        return wdev_type_str._40_4_;
      }
    }
  }
  return wdev_type_str._48_4_;
}

