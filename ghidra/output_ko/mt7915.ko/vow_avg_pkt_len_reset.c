// module: mt7915.ko
// function: vow_avg_pkt_len_reset @ 0x4a198
// size: 24 bytes
//

void vow_avg_pkt_len_reset(int param_1)

{
  *(undefined4 *)(param_1 + 0xa7be38) = 0;
  *(undefined1 *)(param_1 + 0xa7be3c) = 0;
  return;
}

