// module: plat-zxylzb_9128S.ko
// function: idm_check_tx_done_lock @ 0x153fc
// size: 40 bytes
//

void idm_check_tx_done_lock(void)

{
  undefined4 uVar1;
  undefined4 extraout_r2;
  undefined4 in_r3;
  
  uVar1 = _raw_spin_lock_irqsave(&idm_lock_tx);
  idm_check_tx_done_nolock();
  _raw_spin_unlock_irqrestore(&idm_lock_tx,uVar1,extraout_r2,in_r3);
  return;
}

