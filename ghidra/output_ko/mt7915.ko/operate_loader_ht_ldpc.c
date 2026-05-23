// module: mt7915.ko
// function: operate_loader_ht_ldpc @ 0x107918
// size: 20 bytes
//

void operate_loader_ht_ldpc(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0xb) = param_2;
  *(byte *)(param_1 + 0x36) = *(byte *)(param_1 + 0x36) & 0xfe | param_2 & 1;
  return;
}

