// module: mt7915.ko
// function: hc_get_chip_wtbl_max_num @ 0xaabf0
// size: 12 bytes
//

undefined2 hc_get_chip_wtbl_max_num(int param_1)

{
  return *(undefined2 *)(param_1 + 0xd2a);
}

