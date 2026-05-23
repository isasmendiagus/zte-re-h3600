// module: mt7915.ko
// function: GetHashID @ 0xa076c
// size: 20 bytes
//

uint GetHashID(int param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = *(byte *)(param_1 + 5) & 0x3f;
  }
  return uVar1;
}

