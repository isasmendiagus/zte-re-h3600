// module: mt7915.ko
// function: get_cent_ch_by_htinfo @ 0x137c48
// size: 76 bytes
//

byte get_cent_ch_by_htinfo(undefined4 param_1,byte *param_2,byte *param_3)

{
  byte bVar1;
  
  bVar1 = *param_2;
  if ((2 < bVar1) && ((param_2[1] & 3) == 3)) {
    if ((*param_3 & 2) != 0) {
      bVar1 = bVar1 - 2;
    }
    return bVar1;
  }
  if ((param_2[1] & 3) == 1) {
    if ((*param_3 & 2) != 0) {
      bVar1 = bVar1 + 2;
    }
    return bVar1;
  }
  return bVar1;
}

