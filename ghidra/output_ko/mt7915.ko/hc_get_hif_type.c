// module: mt7915.ko
// function: hc_get_hif_type @ 0xaab98
// size: 8 bytes
//

undefined4 hc_get_hif_type(int param_1)

{
  return *(undefined4 *)(param_1 + 0xb64);
}

