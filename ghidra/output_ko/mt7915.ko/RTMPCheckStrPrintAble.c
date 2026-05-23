// module: mt7915.ko
// function: RTMPCheckStrPrintAble @ 0xdb694
// size: 76 bytes
//

undefined4 RTMPCheckStrPrintAble(byte *param_1,int param_2)

{
  byte *pbVar1;
  
  if (param_2 == 0) {
    return 1;
  }
  if (*param_1 - 0x20 < 0x5f) {
    pbVar1 = param_1 + (param_2 - 1U & 0xff);
    do {
      if (param_1 == pbVar1) {
        return 1;
      }
      param_1 = param_1 + 1;
    } while (*param_1 - 0x20 < 0x5f);
  }
  return 0;
}

