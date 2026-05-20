// module: mt7915.ko
// function: WscGetAuthTypeStr @ 0x1e5ef0
// size: 180 bytes
//

char * WscGetAuthTypeStr(uint param_1)

{
  if (param_1 == 5) {
    return "WEPAUTO";
  }
  if (param_1 < 6) {
    if (param_1 == 2) {
      return "WPAPSK";
    }
    if (param_1 == 4) {
      return "SHARED";
    }
    if (param_1 == 1) {
      return "OPEN";
    }
  }
  else {
    if (param_1 == 0x10) {
      return "WPA2";
    }
    if (param_1 < 0x11) {
      if (param_1 == 8) {
        return "WPA";
      }
    }
    else {
      if (param_1 == 0x20) {
        return "WPA2PSK";
      }
      if (param_1 == 0x80) {
        return "WPANONE";
      }
    }
  }
  return "WPAPSKWPA2PSK";
}

