// module: mt7915.ko
// function: mt_clientSupportsETxBF @ 0x85468
// size: 88 bytes
//

uint mt_clientSupportsETxBF(undefined4 param_1,byte *param_2,int param_3)

{
  byte bVar1;
  
  bVar1 = *param_2;
  if (param_3 == 0 && ((param_2[2] & 1) != 0 || (char)param_2[1] < '\0')) {
    return ((uint)bVar1 << 0x1c) >> 0x1f;
  }
  if ((bVar1 & 8) != 0) {
    return (uint)(((uint)param_2[1] << 0x19) >> 0x1e != 0);
  }
  return bVar1 & 8;
}

