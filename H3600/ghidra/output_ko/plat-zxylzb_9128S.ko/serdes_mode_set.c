// module: plat-zxylzb_9128S.ko
// function: serdes_mode_set @ 0x1b7d4
// size: 344 bytes
//

void serdes_mode_set(int param_1)

{
  if (param_1 == 1) {
    *pon_serdes_base = *pon_serdes_base & 0xffffff00 | 0xa5;
    pon_serdes_base[2] = pon_serdes_base[2] & 0xffffff00 | 0x20;
    pon_serdes_base[5] = pon_serdes_base[5] & 0xffff00ff | 0x5800;
    pon_serdes_base[8] = pon_serdes_base[8] & 0xffffff;
    pon_serdes_base[9] = pon_serdes_base[9] & 0xffffff00 | 3;
    pon_serdes_base[9] = pon_serdes_base[9] & 0xff00ffff | 0x570000;
    pon_serdes_base[9] = pon_serdes_base[9] & 0xffffff | 0x7000000;
    return;
  }
  if (param_1 != 3) {
    return;
  }
  *pon_serdes_base = *pon_serdes_base & 0xffffff00 | 0xa5;
  pon_serdes_base[2] = pon_serdes_base[2] & 0xffffff00 | 0x20;
  pon_serdes_base[3] = pon_serdes_base[3] & 0xffffff00 | 5;
  pon_serdes_base[5] = pon_serdes_base[5] & 0xffff00ff | 0x5800;
  pon_serdes_base[8] = pon_serdes_base[8] & 0xffffff;
  pon_serdes_base[9] = pon_serdes_base[9] & 0xffffff00 | 0x83;
  return;
}

