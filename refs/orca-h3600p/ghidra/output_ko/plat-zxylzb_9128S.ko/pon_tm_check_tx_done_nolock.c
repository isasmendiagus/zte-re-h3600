// module: plat-zxylzb_9128S.ko
// function: pon_tm_check_tx_done_nolock @ 0x190e4
// size: 88 bytes
//

void pon_tm_check_tx_done_nolock(int param_1)

{
  if (param_1 != 1) {
    net_txq._16_4_ = net_txq._16_4_ - (*(uint *)(tm_base + 0x10058) & 0xffff);
    return;
  }
  net_txq._44_4_ = net_txq._44_4_ - (*(uint *)(tm_base + 0x10068) & 0xffff);
  return;
}

