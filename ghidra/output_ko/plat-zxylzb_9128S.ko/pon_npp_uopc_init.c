// module: plat-zxylzb_9128S.ko
// function: pon_npp_uopc_init @ 0x14b60
// size: 44 bytes
//

undefined4 pon_npp_uopc_init(void)

{
  *(uint *)(npp_base + 0x18000) = *(uint *)(npp_base + 0x18000) | 8;
  return 0;
}

