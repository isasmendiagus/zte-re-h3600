// module: mt7915.ko
// function: hc_get_asic_cap @ 0xaaba0
// size: 8 bytes
//

undefined4 hc_get_asic_cap(int param_1)

{
  return *(undefined4 *)(param_1 + 0xb58);
}

