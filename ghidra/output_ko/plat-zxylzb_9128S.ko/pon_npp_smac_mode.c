// module: plat-zxylzb_9128S.ko
// function: pon_npp_smac_mode @ 0x1474c
// size: 52 bytes
//

void pon_npp_smac_mode(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = (param_1 + 0x18) * 4;
  *(uint *)(npp_base + iVar1) = *(uint *)(npp_base + iVar1) & 0xfc7fffff | param_2;
  return;
}

