// module: plat-zxylzb_9128S.ko
// function: pon_is_registered @ 0x1b7cc
// size: 52 bytes
//

bool pon_is_registered(void)

{
  if (lan_up == 0) {
    return pon_registered != 0;
  }
  return true;
}

