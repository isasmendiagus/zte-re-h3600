// module: plat-zxylzb_9128S.ko
// function: serdes_set_check_en_open @ 0x1b684
// size: 80 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void serdes_set_check_en_open(void)

{
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) & 0xbfffffff;
  (*_request_threaded_irq)(0xa3d6f8);
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) | 0x40000000;
  return;
}

