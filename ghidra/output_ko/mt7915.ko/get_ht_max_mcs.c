// module: mt7915.ko
// function: get_ht_max_mcs @ 0x137ac8
// size: 72 bytes
//

uint get_ht_max_mcs(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0x1f;
  while( true ) {
    uVar2 = 1 << (uVar1 & 7) & 0xff;
    if ((((uVar2 & *(byte *)(param_1 + ((int)uVar1 >> 3))) != 0) &&
        ((uVar2 & *(byte *)(param_2 + ((int)uVar1 >> 3))) != 0)) || (uVar1 == 0)) break;
    uVar1 = uVar1 - 1;
  }
  return uVar1;
}

