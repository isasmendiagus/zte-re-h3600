// module: mt7915.ko
// function: is_testmode_wdev @ 0x14d280
// size: 40 bytes
//

bool is_testmode_wdev(int param_1)

{
  if ((param_1 - 0x2000U & 0xffffdfff) == 0) {
    return true;
  }
  return (param_1 - 0x800U & 0xfffff7ff) == 0;
}

