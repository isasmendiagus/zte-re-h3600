// module: plat-zxylzb_9128S.ko
// function: idm_timer_func @ 0x15428
// size: 184 bytes
//

void idm_timer_func(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 in_r3;
  
  if (idm_tx_scan != 0) {
    idm_check_tx_done_lock();
  }
  if ((idm_net_check_speed != 0) && (idm_check_cnt = idm_check_cnt + 1, 99 < idm_check_cnt)) {
    uVar2 = *(int *)(idm_netdev._4_4_ + 0x4d4) + *(int *)((int)idm_netdev + 0x4d4);
    if (uVar2 < idm_last_rx_bytes) {
      uVar1 = (idm_last_rx_bytes - 1) - uVar2;
    }
    else {
      uVar1 = uVar2 - idm_last_rx_bytes;
    }
    idm_check_cnt = 0;
    idm_last_rx_bytes = uVar2;
    if (0xfffff < uVar1) {
      idm_net_check_speed = 0;
    }
  }
  idm_poll_cnt = idm_poll_cnt + 1;
  idm_timer._8_4_ = jiffies + 1;
  add_timer(idm_timer,idm_poll_cnt,idm_timer._8_4_,in_r3);
  return;
}

