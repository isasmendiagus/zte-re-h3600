// module: plat-zxylzb_9128S.ko
// function: pon_tm_timer_func @ 0x19234
// size: 212 bytes
//

void pon_tm_timer_func(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  
  puVar1 = net_txq;
  iVar2 = 0;
  do {
    if (*(int *)(puVar1 + 0x10) != 0) {
      uVar3 = 0;
      if ((*(uint *)(((uint)&stack0xffffffe8 & 0xffffe000) + 4) & 0x1fff00) == 0) {
        uVar3 = _raw_spin_lock_irqsave();
      }
      else {
        _raw_spin_lock(&net_lock_tx);
      }
      pon_tm_check_tx_done_nolock(iVar2);
      if ((*(uint *)(((uint)&stack0xffffffe8 & 0xffffe000) + 4) & 0x1fff00) == 0) {
        _raw_spin_unlock_irqrestore();
      }
      else {
        _raw_spin_unlock(&net_lock_tx,uVar3);
      }
    }
    bVar4 = iVar2 != 1;
    puVar1 = puVar1 + 0x1c;
    iVar2 = 1;
  } while (bVar4);
  pon_tm_timer._8_4_ = jiffies + 1;
  pon_tm_poll_cnt = pon_tm_poll_cnt + 1;
  add_timer(pon_tm_timer);
  return;
}

