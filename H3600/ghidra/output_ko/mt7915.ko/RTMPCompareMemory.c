// module: mt7915.ko
// function: RTMPCompareMemory @ 0x13a484
// size: 92 bytes
//

undefined4 RTMPCompareMemory(byte *param_1,byte *param_2,int param_3)

{
  byte *pbVar1;
  
  if (param_3 == 0) {
    return 0;
  }
  if (*param_2 < *param_1) {
    return 1;
  }
  if (*param_2 <= *param_1) {
    pbVar1 = param_1 + param_3;
    do {
      param_1 = param_1 + 1;
      if (param_1 == pbVar1) {
        return 0;
      }
      param_2 = param_2 + 1;
      if (*param_2 < *param_1) {
        return 1;
      }
    } while (*param_2 <= *param_1);
  }
  return 2;
}

