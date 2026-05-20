// module: mt7915.ko
// function: entrytb_aid_bitmap_reserve @ 0x14ad1c
// size: 16 bytes
//

void entrytb_aid_bitmap_reserve(int param_1,uint param_2)

{
  *(short *)(param_1 + 4) = (short)(1 << (param_2 & 0xff));
  return;
}

