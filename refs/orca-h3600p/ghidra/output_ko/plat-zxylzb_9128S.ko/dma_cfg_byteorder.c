// module: plat-zxylzb_9128S.ko
// function: dma_cfg_byteorder @ 0x18c7c
// size: 52 bytes
//

void dma_cfg_byteorder(int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(tm_base + 0x10000) & 0xfff0ffff;
  if (param_1 == 0) {
    uVar1 = uVar1 | 0x200000;
  }
  else {
    uVar1 = uVar1 | 0x2f0000;
  }
  *(uint *)(tm_base + 0x10000) = uVar1;
  return;
}

