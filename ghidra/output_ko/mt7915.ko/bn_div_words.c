// module: mt7915.ko
// function: bn_div_words @ 0x20eb18
// size: 20 bytes
//

ulong bn_div_words(ulong h,ulong l,ulong d)

{
  ulong uVar1;
  
  if (d == 0) {
    return 0xffffffff;
  }
  uVar1 = FUN_0020d060();
  return uVar1;
}

