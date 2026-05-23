// module: mt7915.ko
// function: mt_cmd_get_rx_stat_comm_rsp @ 0x1ac144
// size: 12 bytes
//

void mt_cmd_get_rx_stat_comm_rsp(int param_1,void *param_2)

{
  os_move_mem(*(void **)(param_1 + 0xc),param_2,0xc);
  return;
}

