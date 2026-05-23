// module: mt7915.ko
// function: mt7915_hif_ctrl_chip_init @ 0x188f2c
// size: 88 bytes
//

void mt7915_hif_ctrl_chip_init(undefined4 *param_1)

{
  param_1[0x32] = rx_ring_layout;
  *param_1 = 0x3cf38007;
  param_1[1] = 0xd7014;
  param_1[0x1b1] = 0xc0;
  param_1[0x31] = tx_ring_layout;
  param_1[0x36] = mt7915_isr;
  *(undefined1 *)(param_1 + 4) = 5;
  *(undefined1 *)((int)param_1 + 0x11) = 5;
  return;
}

