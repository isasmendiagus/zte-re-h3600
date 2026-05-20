// module: mt7915.ko
// function: SecAuthModeNewToOld @ 0x113630
// size: 168 bytes
//

undefined4 SecAuthModeNewToOld(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 & 1) != 0) {
    return 0;
  }
  if ((param_1 & 2) != 0) {
    return 1;
  }
  if ((param_1 & 4) != 0) {
    return 2;
  }
  if ((param_1 & 0x20) != 0) {
    return 5;
  }
  if ((param_1 & 0x48) == 0x48) {
    return 8;
  }
  if ((param_1 & 0x90) == 0x90) {
    return 9;
  }
  if ((param_1 & 8) != 0) {
    return 3;
  }
  if ((param_1 & 0x10) == 0) {
    if ((param_1 & 0x40) == 0) {
      if ((param_1 & 0x80) == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 7;
      }
      return uVar1;
    }
    return 6;
  }
  return 4;
}

