// module: mt7915.ko
// function: vow_reset_dvt @ 0x48d94
// size: 224 bytes
//

void vow_reset_dvt(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined1 *)(param_1 + 0xa7a31a) = 0;
  __memzero(vow_tx_time,0x480,param_3,param_4,param_4);
  __memzero(vow_rx_time,0x480);
  __memzero(vow_tx_ok,0x480);
  __memzero(vow_tx_fail,0x480);
  __memzero(vow_last_tx_time,0x480);
  __memzero(vow_last_rx_time,0x480);
  __memzero(vow_tx_bss_byte,0x10);
  __memzero(vow_rx_bss_byte,0x10);
  __memzero(vow_tx_mbss_byte,0x40);
  __memzero(vow_rx_mbss_byte,0x40);
  vow_sum_tx_rx_time = 0;
  vow_avg_sum_time = 0;
  vow_ampdu_cnt = 0;
  vow_interval = 0;
  vow_last_free_cnt = 0;
  vow_idx = 0;
  return;
}

