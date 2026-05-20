// module: mt7915.ko
// function: operate_loader_ht_gi @ 0x10792c
// size: 52 bytes
//

void operate_loader_ht_gi(int param_1,int param_2,int param_3)

{
  bool bVar1;
  
  bVar1 = param_3 == 1;
  if (bVar1) {
    param_2 = param_2 + -1;
  }
  *(char *)(param_1 + 0xc) = (char)param_3;
  *(byte *)(param_1 + 0x36) =
       *(byte *)(param_1 + 0x36) & 0x9f | bVar1 << 5 | (bVar1 && param_2 == 0) << 6;
  return;
}

