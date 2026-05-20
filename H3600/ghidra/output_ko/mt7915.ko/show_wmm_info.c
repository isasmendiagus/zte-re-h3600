// module: mt7915.ko
// function: show_wmm_info @ 0xe1304
// size: 28 bytes
//

undefined4 show_wmm_info(int param_1)

{
  hc_show_edca_info(*(undefined4 *)(param_1 + 0xa797a0));
  return 1;
}

