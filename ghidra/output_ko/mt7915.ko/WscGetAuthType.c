// module: mt7915.ko
// function: WscGetAuthType @ 0x1e5e14
// size: 152 bytes
//

undefined4 WscGetAuthType(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 & 1) != 0) {
    return 1;
  }
  if ((param_1 & 2) != 0) {
    return 4;
  }
  if ((param_1 & 0x20) != 0) {
    return 0x80;
  }
  if ((param_1 & 0x48) == 0x48) {
    return 0x18;
  }
  if ((param_1 & 0x90) == 0x90) {
    return 0x22;
  }
  if ((param_1 & 8) != 0) {
    return 8;
  }
  if ((param_1 & 0x10) != 0) {
    return 2;
  }
  if ((param_1 & 0x40) == 0) {
    if ((param_1 & 0x80) == 0) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0x20;
    }
    return uVar1;
  }
  return 0x10;
}

