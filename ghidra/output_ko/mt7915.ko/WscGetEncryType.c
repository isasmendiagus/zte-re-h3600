// module: mt7915.ko
// function: WscGetEncryType @ 0x1e5eac
// size: 68 bytes
//

undefined4 WscGetEncryType(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 & 1) != 0) {
    return 1;
  }
  if ((param_1 & 0xe) == 0) {
    if ((param_1 & 0x30) == 0x30) {
      return 0xc;
    }
    if ((param_1 & 0x10) == 0) {
      uVar1 = 8;
    }
    else {
      uVar1 = 4;
    }
    return uVar1;
  }
  return 2;
}

