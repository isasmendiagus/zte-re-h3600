// module: plat-zxylzb_9128S.ko
// function: pon_pp_cla_init @ 0x17f88
// size: 56 bytes
//

undefined4 pon_pp_cla_init(void)

{
  *(undefined4 *)(pp_base + 0xc080) = 0x1000;
  *(undefined4 *)(pp_base + 0xc084) = 2;
  return 0;
}

