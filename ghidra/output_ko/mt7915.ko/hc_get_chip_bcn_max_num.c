// module: mt7915.ko
// function: hc_get_chip_bcn_max_num @ 0xaabe8
// size: 8 bytes
//

undefined1 hc_get_chip_bcn_max_num(int param_1)

{
  return *(undefined1 *)(param_1 + 0xbc0);
}

