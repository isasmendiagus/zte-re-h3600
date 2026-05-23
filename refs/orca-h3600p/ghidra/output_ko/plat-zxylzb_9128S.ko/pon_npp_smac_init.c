// module: plat-zxylzb_9128S.ko
// function: pon_npp_smac_init @ 0x1460c
// size: 240 bytes
//

undefined4 pon_npp_smac_init(void)

{
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  undefined5 *puVar5;
  
  gephy_ldo_init();
  iVar2 = 0x40000;
  uVar1 = 0;
  puVar3 = &uni_phy;
  puVar4 = (undefined4 *)uni_phy_stat;
  puVar5 = &has_phy_int;
  do {
    zx_mdio_write(*puVar3,0x10,0x8001);
    zx_mdio_write(*puVar3,0x11,0);
    smac_init(uVar1 & 0xff);
    *(uint *)(npp_base + iVar2) = *(uint *)(npp_base + iVar2) | 2;
    uVar1 = uVar1 + 1;
    iVar2 = iVar2 + 0x40000;
    *puVar4 = 0xffffffff;
    *(undefined1 *)puVar5 = 1;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
    puVar5 = (undefined5 *)((int)puVar5 + 1);
  } while (uVar1 != 4);
  phy_process(0);
  init_timer_key(gephy_ldo_timer,0,0,0);
  gephy_ldo_timer._8_4_ = jiffies + 200;
  gephy_ldo_timer._16_4_ = gephy_ldo_timer_func;
  gephy_ldo_timer._20_4_ = 0;
  add_timer(gephy_ldo_timer);
  register_phy_int();
  return 0;
}

