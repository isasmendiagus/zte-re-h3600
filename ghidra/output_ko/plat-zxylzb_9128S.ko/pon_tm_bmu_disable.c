// module: plat-zxylzb_9128S.ko
// function: pon_tm_bmu_disable @ 0x18630
// size: 28 bytes
//

void pon_tm_bmu_disable(void)

{
  *(undefined4 *)(tm_base + 0x8000) = 0;
  return;
}

