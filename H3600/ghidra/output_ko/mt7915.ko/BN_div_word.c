// module: mt7915.ko
// function: BN_div_word @ 0x2113a8
// size: 40 bytes
//

ulong BN_div_word(BIGNUM *a,ulong w)

{
  ulong uVar1;
  
  if (w == 0) {
    return 0xffffffff;
  }
  if (a->top == 0) {
    return 0;
  }
  uVar1 = FUN_00210b14();
  return uVar1;
}

