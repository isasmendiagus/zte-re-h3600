// module: mt7915.ko
// function: RandomByte @ 0x12f300
// size: 88 bytes
//

byte RandomByte(void)

{
  byte bVar1;
  int iVar2;
  bool bVar3;
  uint local_c [2];
  
  get_random_bytes(local_c,4);
  iVar2 = 8;
  bVar1 = 0;
  do {
    bVar3 = (local_c[0] & 1) == 0;
    if (bVar3) {
      local_c[0] = local_c[0] >> 1;
    }
    else {
      local_c[0] = (local_c[0] ^ 0x80000057) >> 1 | 0x80000000;
    }
    iVar2 = iVar2 + -1;
    bVar1 = !bVar3 | bVar1 << 1;
  } while (iVar2 != 0);
  return bVar1;
}

