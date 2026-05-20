// module: mt7915.ko
// function: SecHWCipherSuitMapping @ 0x11372c
// size: 112 bytes
//

undefined4 SecHWCipherSuitMapping(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 & 1) != 0) {
    return 0;
  }
  if ((param_1 & 0xe) != 0) {
    return 1;
  }
  if ((param_1 & 0x10) != 0) {
    return 2;
  }
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 0x40) != 0) {
      return 10;
    }
    if ((param_1 & 0x80) == 0) {
      if ((param_1 & 0x100) == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 0xc;
      }
      return uVar1;
    }
    return 0xb;
  }
  return 4;
}

