// module: plat-zxylzb_9128S.ko
// function: pon_npp_smac_disable.part.4 @ 0x13f80
// size: 48 bytes
//

void pon_npp_smac_disable_part_4(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x40000 + 0x40000;
  *(uint *)(npp_base + iVar1) = *(uint *)(npp_base + iVar1) & 0xfffffffc;
  return;
}

