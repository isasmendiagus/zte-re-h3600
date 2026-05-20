// module: mt7915.ko
// function: GetEncryModeStr @ 0x1134fc
// size: 252 bytes
//

char * GetEncryModeStr(uint param_1)

{
  char *pcVar1;
  
  if ((param_1 & 1) != 0) {
    return "NONE";
  }
  if ((param_1 & 0xe) != 0) {
    return "WEP";
  }
  if ((param_1 & 0x30) == 0x30) {
    return "TKIPAES";
  }
  if ((param_1 & 0x10) != 0) {
    return "TKIP";
  }
  if ((param_1 & 0x20) != 0) {
    return "AES";
  }
  if ((param_1 & 0x40) != 0) {
    return "CCMP256";
  }
  if ((param_1 & 0x80) != 0) {
    return "GCMP128";
  }
  if ((param_1 & 0x100) == 0) {
    if ((param_1 & 0x200) != 0) {
      return "BIP-CMAC128";
    }
    if ((param_1 & 0x400) == 0) {
      if ((param_1 & 0x800) == 0) {
        pcVar1 = "BIP-GMAC256";
        if ((param_1 & 0x1000) == 0) {
          pcVar1 = "UNKNOW";
        }
        return pcVar1;
      }
      return "BIP-GMAC128";
    }
    return "BIP-CMAC256";
  }
  return "GCMP256";
}

