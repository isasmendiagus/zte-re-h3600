// module: plat-zxylzb_9128S.ko
// function: pon_tm_bmu_enable @ 0x1864c
// size: 28 bytes
//

void pon_tm_bmu_enable(void)

{
  *(undefined4 *)(tm_base + 0x8000) = 1;
  return;
}

