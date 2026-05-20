// module: mt7915.ko
// function: ZTE_tx_ctrl_rate_stat_init @ 0x15be44
// size: 92 bytes
//

void ZTE_tx_ctrl_rate_stat_init(undefined4 param_1,int param_2)

{
  os_alloc_mem(param_1,param_2 + 0x14b0,0x1040);
  if (*(int *)(param_2 + 0x14b0) != 0) {
    __memzero(*(int *)(param_2 + 0x14b0),0x1040);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s Fail to alloc memory for perPktStat\n","ZTE_tx_ctrl_rate_stat_init");
  return;
}

