// module: mt7915.ko
// function: rlmCalCacheDone @ 0x1c85cc
// size: 56 bytes
//

uint rlmCalCacheDone(uint *param_1)

{
  uint uVar1;
  
  uVar1 = *param_1;
  return (uint)((uVar1 & 0x18) == 0x18) & uVar1 >> 5 & uVar1 >> 6 & uVar1 >> 7 & uVar1 >> 8 &
         uVar1 >> 9 & uVar1 >> 10 & uVar1 >> 0xb & uVar1 >> 0xc;
}

