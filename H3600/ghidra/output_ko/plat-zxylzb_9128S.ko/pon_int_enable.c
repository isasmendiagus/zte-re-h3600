// module: plat-zxylzb_9128S.ko
// function: pon_int_enable @ 0x1b2e4
// size: 40 bytes
//

void pon_int_enable(uint param_1)

{
  *(uint *)(pon_base + 0x40044) = *(uint *)(pon_base + 0x40044) & ~param_1;
  return;
}

