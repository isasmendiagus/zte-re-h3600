// module: mt7915.ko
// function: mt_cmd_get_rx_stat_user_rsp @ 0x1ac138
// size: 12 bytes
//

void mt_cmd_get_rx_stat_user_rsp(int param_1,void *param_2)

{
  os_move_mem(*(void **)(param_1 + 0xc),param_2,4);
  return;
}

