// module: mt7915.ko
// function: GetExtCh @ 0x141128
// size: 24 bytes
//

uint GetExtCh(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 1) {
    uVar1 = param_1 + 4;
  }
  else {
    uVar1 = param_1 - 4U & ~((int)(param_1 - 4U) >> 0x1f);
  }
  return uVar1 & 0xff;
}

