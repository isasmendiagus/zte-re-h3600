// module: plat-zxylzb_9128S.ko
// function: reg_def_set @ 0x1c2c4
// size: 344 bytes
//

void reg_def_set(void)

{
  *pon_serdes_base = 0x800180a7;
  pon_serdes_base[1] = 0x8f;
  pon_serdes_base[2] = 0x540;
  pon_serdes_base[3] = 4;
  pon_serdes_base[4] = 0;
  pon_serdes_base[5] = 0x18a6400;
  pon_serdes_base[6] = 0xb50140;
  pon_serdes_base[7] = 0x1216000;
  pon_serdes_base[8] = 0x40000000;
  pon_serdes_base[9] = 0xb510007;
  pon_serdes_base[10] = 0;
  pon_serdes_base[0xb] = 0;
  pon_serdes_base[0xc] = 0xa02e2400;
  pon_serdes_base[0xd] = 0xc0593d44;
  pon_serdes_base[0xe] = 0xf0f;
  pon_serdes_base[0xf] = 0;
  pon_serdes_base[0x10] = 0x3c0000;
  pon_serdes_base[0x11] = 0xea00a013;
  pon_serdes_base[0x12] = 0x101038ca;
  pon_serdes_base[0x13] = 0x5a008;
  pon_serdes_base[0x14] = 0x33333333;
  pon_serdes_base[0x15] = 0x33333333;
  pon_serdes_base[0x16] = 0x3e23333;
  pon_serdes_base[0x17] = 0x40244;
  return;
}

