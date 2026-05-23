// module: plat-zxylzb_9128S.ko
// function: zx5201_config @ 0x14780
// size: 520 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zx5201_config(void)

{
  undefined4 uVar1;
  undefined4 in_r3;
  uint uVar2;
  
  DataSynchronizationBarrier(0xf);
  uVar2 = uRamf060000c & 0xffe7f7ff;
  DataSynchronizationBarrier(0xe);
  if (_kallsyms_lookup != (code *)0x0) {
    (*_kallsyms_lookup)();
  }
  uRamf060000c = uVar2;
  zx_mdio_write(8,0x12,0x8402);
  zx_mdio_write(9,0x16,0xa0f);
  zx_mdio_write(9,0x1b,0x800);
  zx_mdio_write(8,0x1d,0x355);
  zx_mdio_write(8,0x10,0xb62d);
  zx_mdio_write(8,0x11,6);
  zx_mdio_write(9,0x12,4);
  uVar2 = zx_mdio_read(9,0x15);
  uVar1 = zx_mdio_read(9,0x14);
  zx_mdio_write(9,0x11,uVar2 & 0xc1ff | 0x2800);
  zx_mdio_write(9,0x10,uVar1);
  zx_mdio_write(9,0x12,0x204);
  uVar2 = zx_mdio_read(9,0x16);
  zx_mdio_write(9,0x16,uVar2 & 0xfff3 | 4);
  if (product_vid != ' ') {
    return;
  }
  uVar2 = zx_mdio_read(9,0x17);
  zx_mdio_write(9,0x17,uVar2 & 0xfff9);
  uVar2 = zx_mdio_read(9,0x17);
  zx_mdio_write(9,0x17,uVar2 & 0xfffe);
  zx_mdio_write(8,0x10,0xb409);
  zx_mdio_write(8,0x11,0);
  zx_mdio_write(8,0x10,0xb407);
  zx_mdio_write(8,0x11,0);
  zx_mdio_write(8,0x10,0xb406);
  zx_mdio_write(8,0x11,0);
  zx_mdio_write(8,0x10,0xb408);
  zx_mdio_write(8,0x11,0,in_r3);
  return;
}

