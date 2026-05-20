// module: idmfdb.ko
// function: idm_led_exit @ 0x126f0
// size: 84 bytes
//

void idm_led_exit(void)

{
  if (DAT_0001801c != '\0') {
    DAT_0001801c = '\0';
    del_timer_sync(&DAT_00018030);
  }
  if (DAT_0001805c == '\0') {
    return;
  }
  DAT_0001805c = 0;
  del_timer_sync(&DAT_00018070);
  return;
}

