// module: mt7915.ko
// function: SecEncryModeNewToOld @ 0x1136d8
// size: 84 bytes
//

undefined4 SecEncryModeNewToOld(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 & 1) != 0) {
    return 1;
  }
  if ((param_1 & 0xe) != 0) {
    return 0;
  }
  if ((param_1 & 0x10) != 0) {
    return 4;
  }
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 0x30) == 0x30) {
      uVar1 = 0xb;
    }
    else {
      uVar1 = 1;
    }
    return uVar1;
  }
  return 6;
}

