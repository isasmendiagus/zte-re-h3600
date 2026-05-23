// module: mt7915.ko
// function: raMaxRssi @ 0x1d90e8
// size: 52 bytes
//

int raMaxRssi(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 4);
  if (bVar1 != 1) {
    if (bVar1 < 2) {
      param_2 = -100;
    }
    else {
      if (param_2 < param_3) {
        param_2 = param_3;
      }
      if ((bVar1 != 2) && (param_2 < param_4)) {
        param_2 = param_4;
      }
    }
  }
  return param_2;
}

