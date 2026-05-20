// module: plat-zxylzb_9128S.ko
// function: pon_tm_net_timeout @ 0x19210
// size: 36 bytes
//

void pon_tm_net_timeout(int param_1)

{
  netif_tx_wake_queue(*(undefined4 *)(param_1 + 0x240));
  *(undefined4 *)(param_1 + 0x260) = jiffies;
  return;
}

