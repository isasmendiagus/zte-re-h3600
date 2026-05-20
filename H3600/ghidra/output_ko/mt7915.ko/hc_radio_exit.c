// module: mt7915.ko
// function: hc_radio_exit @ 0xa9224
// size: 28 bytes
//

undefined4 hc_radio_exit(int param_1)

{
  rc_radio_exit(*(undefined4 *)(param_1 + 0xa797a0));
  return 0;
}

