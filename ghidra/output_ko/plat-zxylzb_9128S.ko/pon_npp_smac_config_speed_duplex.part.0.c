// module: plat-zxylzb_9128S.ko
// function: pon_npp_smac_config_speed_duplex.part.0 @ 0x13ef4
// size: 92 bytes
//

void pon_npp_smac_config_speed_duplex_part_0(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = param_1 * 0x40000 + 0x40000;
  uVar2 = *(uint *)(npp_base + iVar1);
  if (param_2 == 2) {
    uVar2 = uVar2 & 0xffff7fff | 0x2000;
  }
  else {
    if (param_3 == 0) {
      uVar2 = uVar2 & 0xffffdfff | 0x8000;
    }
    else {
      uVar2 = uVar2 | 0xa000;
    }
    if (param_2 == 1) {
      uVar2 = uVar2 | 0x4000;
    }
    else {
      uVar2 = uVar2 & 0xffffbfff;
    }
  }
  *(uint *)(npp_base + iVar1) = uVar2;
  return;
}

