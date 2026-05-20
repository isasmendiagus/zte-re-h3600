// module: mt7915.ko
// function: sec_get_cipher_key_len @ 0x1188b4
// size: 64 bytes
//

undefined4 sec_get_cipher_key_len(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 & 0x10) != 0) {
    return 0x20;
  }
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 0x40) != 0) {
      return 0x20;
    }
    if ((param_1 & 0x80) == 0) {
      if ((param_1 & 0x100) == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 0x20;
      }
      return uVar1;
    }
  }
  return 0x10;
}

