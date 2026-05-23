// module: mt7915.ko
// function: bssid_num_to_max_indicator @ 0x51bdc
// size: 52 bytes
//

void bssid_num_to_max_indicator(uint param_1)

{
  sbyte sVar1;
  
  sVar1 = 0;
  if (param_1 < 2) {
    return;
  }
  do {
    sVar1 = sVar1 + 1;
  } while ((1 << sVar1 & 0xffU) < param_1);
  return;
}

