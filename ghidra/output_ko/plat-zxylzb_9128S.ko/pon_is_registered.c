// module: plat-zxylzb_9128S.ko
// function: pon_is_registered @ 0x1b1ec
// size: 52 bytes
//

undefined4 pon_is_registered(void)

{
  if ((lan_up == 0) && (pon_registered == 0)) {
    pon_registered = 1;
  }
  return 1;
}

