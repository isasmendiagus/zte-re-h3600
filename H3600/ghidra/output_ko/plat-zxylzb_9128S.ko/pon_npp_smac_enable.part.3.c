// module: plat-zxylzb_9128S.ko
// function: pon_npp_smac_enable.part.3 @ 0x13f50
// size: 48 bytes
//

void pon_npp_smac_enable_part_3(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x40000 + 0x40000;
  *(uint *)(npp_base + iVar1) = *(uint *)(npp_base + iVar1) | 3;
  return;
}

