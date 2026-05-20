// module: mt7915.ko
// function: GetAuthMode @ 0xdc83c
// size: 212 bytes
//

char * GetAuthMode(int param_1)

{
  char *pcVar1;
  
  if (param_1 == 0) {
    return "OPEN";
  }
  if (param_1 == 1) {
    return "SHARED";
  }
  if (param_1 == 2) {
    return "AUTOWEP";
  }
  if (param_1 == 3) {
    return "WPA";
  }
  if (param_1 == 4) {
    return "WPAPSK";
  }
  if (param_1 == 5) {
    return "WPANONE";
  }
  if (param_1 == 6) {
    return "WPA2";
  }
  if (param_1 != 7) {
    if (param_1 != 8) {
      pcVar1 = "WPA1PSKWPA2PSK";
      if (param_1 != 9) {
        pcVar1 = "UNKNOW";
      }
      return pcVar1;
    }
    return "WPA1WPA2";
  }
  return "WPA2PSK";
}

