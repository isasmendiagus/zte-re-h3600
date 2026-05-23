// module: mt7915.ko
// function: BN_pseudo_rand @ 0x20e58c
// size: 48 bytes
//

int BN_pseudo_rand(BIGNUM *rnd,int bits,int top,int bottom)

{
  int iVar1;
  
  iVar1 = FUN_0020e330(1,rnd,bits,top,bottom);
  return iVar1;
}

