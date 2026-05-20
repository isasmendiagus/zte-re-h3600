// module: plat-zxylzb_9128S.ko
// function: pon_npp_smac_init @ 0x14988
// size: 352 bytes
//

undefined4 pon_npp_smac_init(void)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  undefined5 *puVar6;
  
  gephy_ldo_init();
  iVar3 = 0x40000;
  uVar2 = 0;
  puVar4 = &uni_phy;
  puVar5 = (undefined4 *)uni_phy_stat;
  puVar6 = &has_phy_int;
  do {
    zx_mdio_write(*puVar4,0x10,0x8001);
    zx_mdio_write(*puVar4,0x11,0);
    smac_init(uVar2 & 0xff);
    *(uint *)(npp_base + iVar3) = *(uint *)(npp_base + iVar3) | 2;
    uVar2 = uVar2 + 1;
    iVar3 = iVar3 + 0x40000;
    *(undefined1 *)puVar6 = 1;
    *puVar5 = 0xffffffff;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
    puVar6 = (undefined5 *)((int)puVar6 + 1);
  } while (uVar2 != 4);
  phy_process(0);
  init_timer_key(gephy_ldo_timer,0,0,0);
  gephy_ldo_timer._8_4_ = jiffies + 200;
  gephy_ldo_timer._16_4_ = gephy_ldo_timer_func;
  gephy_ldo_timer._20_4_ = 0;
  add_timer(gephy_ldo_timer);
  register_phy_int();
  zx5201_config();
  init_timer_key(extphy_timer,0,0,0);
  extphy_timer._8_4_ = jiffies + 10;
  extphy_timer._20_4_ = 0;
  extphy_timer._16_4_ = extphy_timer_func;
  add_timer(extphy_timer);
  uni_phy_stat._16_4_ = 0xffffffff;
  uVar2 = (uint)(byte)lan_up_port;
  uVar1 = zx_mdio_read((&uni_phy)[uVar2],0);
  zx_mdio_write((&uni_phy)[uVar2],0,uVar1 | 0x800);
  return 0;
}

