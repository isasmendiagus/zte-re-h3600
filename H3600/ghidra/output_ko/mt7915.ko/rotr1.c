// module: mt7915.ko
// function: rotr1 @ 0x117974
// size: 24 bytes
//

uint rotr1(uint param_1)

{
  uint uVar1;
  
  if ((param_1 & 1) == 0) {
    uVar1 = (param_1 << 0x10) >> 0x11;
  }
  else {
    uVar1 = param_1 >> 1 | 0x8000;
  }
  return uVar1 & 0xffff;
}

