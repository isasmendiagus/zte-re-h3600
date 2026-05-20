// module: plat-zxylzb_9128S.ko
// function: pon_npp_smct_init @ 0x14720
// size: 56 bytes
//

void pon_npp_smct_init(void)

{
  *(undefined4 *)(npp_base + 0x10000) = 0xb;
  *(undefined4 *)(tm_set_onu_mac + npp_base + 4) = 0xb;
  *(undefined4 *)(npp_base + 0x10010) = 0x3810;
  return;
}

