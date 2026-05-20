// module: mt7915.ko
// function: MCSRate2Index @ 0x157af8
// size: 80 bytes
//

int MCSRate2Index(int param_1,byte param_2)

{
  byte bVar1;
  
  if ((param_1 == 0) || (bVar1 = *(byte *)(param_1 + 0xbd) >> 5, bVar1 < 2)) {
    param_2 = 0xff;
  }
  else {
    if ((3 < bVar1) && ((param_2 & 0xf) < 0xc)) {
      return (int)(char)(param_2 & 0xf);
    }
    param_2 = param_2 & 0x3f;
    if (0xf < param_2) {
      param_2 = 0;
    }
  }
  return (int)(char)param_2;
}

