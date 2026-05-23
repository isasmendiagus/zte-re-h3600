// module: mt7915.ko
// function: BtoH @ 0x13bfbc
// size: 68 bytes
//

uint BtoH(uint param_1)

{
  uint uVar1;
  
  param_1 = param_1 & 0xff;
  uVar1 = param_1 - 0x30 & 0xff;
  if (uVar1 < 10) {
    return uVar1;
  }
  if (param_1 - 0x41 < 6) {
    return param_1 - 0x37 & 0xff;
  }
  if (param_1 - 0x61 < 6) {
    uVar1 = param_1 - 0x57 & 0xff;
  }
  else {
    uVar1 = 0xff;
  }
  return uVar1;
}

