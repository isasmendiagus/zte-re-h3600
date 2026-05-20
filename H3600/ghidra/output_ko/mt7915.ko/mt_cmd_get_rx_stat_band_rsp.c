// module: mt7915.ko
// function: mt_cmd_get_rx_stat_band_rsp @ 0x1ac120
// size: 12 bytes
//

void mt_cmd_get_rx_stat_band_rsp(int param_1,void *param_2)

{
  os_move_mem(*(void **)(param_1 + 0xc),param_2,0x20);
  return;
}

