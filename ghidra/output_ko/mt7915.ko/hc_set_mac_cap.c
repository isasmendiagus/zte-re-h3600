// module: mt7915.ko
// function: hc_set_mac_cap @ 0xaaba8
// size: 16 bytes
//

void hc_set_mac_cap(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0xb5c) = *(uint *)(param_1 + 0xb5c) | param_2;
  return;
}

