// module: mt7915.ko
// function: GetEncryptType @ 0xdc7cc
// size: 112 bytes
//

char * GetEncryptType(int param_1)

{
  char *pcVar1;
  
  if (param_1 == 1) {
    return "NONE";
  }
  if (param_1 == 0) {
    return "WEP";
  }
  if (param_1 == 4) {
    return "TKIP";
  }
  if (param_1 != 6) {
    pcVar1 = "TKIPAES";
    if (param_1 != 0xb) {
      pcVar1 = "UNKNOW";
    }
    return pcVar1;
  }
  return "AES";
}

