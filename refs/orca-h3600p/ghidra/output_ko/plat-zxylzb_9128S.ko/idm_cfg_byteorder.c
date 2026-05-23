// module: plat-zxylzb_9128S.ko
// function: idm_cfg_byteorder @ 0x15d9c
// size: 48 bytes
//

void idm_cfg_byteorder(int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(npp_base + 0x8000) & 0xfff0ffff;
  if (param_1 != 0) {
    uVar1 = uVar1 | 0xf0000;
  }
  *(uint *)(npp_base + 0x8000) = uVar1;
  return;
}

