// module: idmfdb.ko
// function: idm_led_exit @ 0x125ac
// size: 84 bytes
//

void idm_led_exit(void)

{
  if (DAT_00017e74 != '\0') {
    DAT_00017e74 = '\0';
    del_timer_sync(&DAT_00017e88);
  }
  if (DAT_00017eb4 == '\0') {
    return;
  }
  DAT_00017eb4 = 0;
  del_timer_sync(&DAT_00017ec8);
  return;
}

