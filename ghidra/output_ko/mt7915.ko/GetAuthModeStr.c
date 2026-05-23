// module: mt7915.ko
// function: GetAuthModeStr @ 0x1133a8
// size: 340 bytes
//

char * GetAuthModeStr(uint param_1)

{
  char *pcVar1;
  
  if ((param_1 & 1) != 0) {
    return "OPEN";
  }
  if ((param_1 & 2) != 0) {
    return "SHARED";
  }
  if ((param_1 & 4) != 0) {
    return "WEPAUTO";
  }
  if ((param_1 & 0x20) != 0) {
    return "WPANONE";
  }
  if ((param_1 & 0x48) == 0x48) {
    return "WPA1WPA2";
  }
  if ((param_1 & 0x90) == 0x90) {
    return "WPAPSKWPA2PSK";
  }
  if ((param_1 & 0x2080) == 0x2080) {
    return "WPA2PSKWPA3PSK";
  }
  if ((param_1 & 0x2000) == 0) {
    if ((param_1 & 8) != 0) {
      return "WPA";
    }
    if ((param_1 & 0x10) != 0) {
      return "WPAPSK";
    }
    if ((param_1 & 0x100) != 0) {
      return "FT-WPA2";
    }
    if ((param_1 & 0x200) == 0) {
      if ((param_1 & 0x800000) != 0) {
        return "WPA3";
      }
      if ((param_1 & 0x40) == 0) {
        if ((param_1 & 0x80) == 0) {
          pcVar1 = "WPA3-192";
          if ((param_1 & 0x10000) == 0) {
            pcVar1 = "UNKNOW";
          }
          return pcVar1;
        }
        return "WPA2PSK";
      }
      return "WPA2";
    }
    return "FT-WPA2PSK";
  }
  return "WPA3PSK";
}

