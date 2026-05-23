// module: plat-zxylzb_9128S.ko
// function: pon_npp_int_enable @ 0x1316c
// size: 32 bytes
//

void pon_npp_int_enable(uint param_1)

{
  *(uint *)(npp_base + 4) = *(uint *)(npp_base + 4) & ~param_1;
  return;
}

