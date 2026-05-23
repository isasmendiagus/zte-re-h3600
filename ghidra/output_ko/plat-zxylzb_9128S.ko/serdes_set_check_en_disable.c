// module: plat-zxylzb_9128S.ko
// function: serdes_set_check_en_disable @ 0x1b6d4
// size: 32 bytes
//

void serdes_set_check_en_disable(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0xbfffffff;
  return;
}

