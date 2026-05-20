// module: mt7915.ko
// function: ZTE_tx_ctrl_rate_stat_destroy @ 0x15bea4
// size: 28 bytes
//

void ZTE_tx_ctrl_rate_stat_destroy(undefined4 param_1,int param_2)

{
  os_free_mem(*(undefined4 *)(param_2 + 0x14b0));
  *(undefined4 *)(param_2 + 0x14b0) = 0;
  return;
}

