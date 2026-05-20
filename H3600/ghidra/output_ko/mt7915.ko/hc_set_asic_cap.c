// module: mt7915.ko
// function: hc_set_asic_cap @ 0xaabc8
// size: 16 bytes
//

void hc_set_asic_cap(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0xb58) = *(uint *)(param_1 + 0xb58) | param_2;
  return;
}

