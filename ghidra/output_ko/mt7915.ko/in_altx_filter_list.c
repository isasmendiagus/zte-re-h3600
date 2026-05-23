// module: mt7915.ko
// function: in_altx_filter_list @ 0x19b1b0
// size: 104 bytes
//

bool in_altx_filter_list(byte *param_1)

{
  byte *pbVar1;
  byte *pbVar2;
  
  pbVar2 = altx_filter_list;
  do {
    pbVar1 = pbVar2 + 1;
    if (*pbVar2 == *param_1 >> 4) {
      return true;
    }
    pbVar2 = pbVar1;
  } while (pbVar1 != &UNK_0029da0e);
  if (*param_1 >> 4 == 0xd) {
    if (param_1[0x18] == 4) {
      return true;
    }
    if (param_1[0x18] == 3) {
      return param_1[0x19] == 1;
    }
  }
  return false;
}

