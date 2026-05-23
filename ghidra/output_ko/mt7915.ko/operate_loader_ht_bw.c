// module: mt7915.ko
// function: operate_loader_ht_bw @ 0x107888
// size: 20 bytes
//

void operate_loader_ht_bw(int param_1)

{
  *(byte *)(param_1 + 0x21) = *(byte *)(param_1 + 0x21) & 0xfb | (*(byte *)(param_1 + 9) & 1) << 2;
  return;
}

