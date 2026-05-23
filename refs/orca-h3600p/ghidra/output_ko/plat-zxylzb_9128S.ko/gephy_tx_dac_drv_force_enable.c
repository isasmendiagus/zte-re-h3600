// module: plat-zxylzb_9128S.ko
// function: gephy_tx_dac_drv_force_enable @ 0x133ec
// size: 620 bytes
//

void gephy_tx_dac_drv_force_enable(int param_1,int param_2)

{
  gephy_flag = 0;
  if (g_phy_dbg_lvl != '\0') {
    printk("Debug:GE%u tx dac drv force:%u",param_1,param_2);
  }
  if (param_2 == 0) {
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb676);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb677);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb667);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb668);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb6c2);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb6c1);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb678);
    zx_mdio_write((&uni_phy)[param_1],0x11,0xf);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb669);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
  }
  else if (param_2 == 1) {
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb676);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb677);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb667);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb668);
    zx_mdio_write((&uni_phy)[param_1],0x11,3);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb6c2);
    zx_mdio_write((&uni_phy)[param_1],0x11,2);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb6c1);
    zx_mdio_write((&uni_phy)[param_1],0x11,1);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb678);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
    zx_mdio_write((&uni_phy)[param_1],0x10,0xb669);
    zx_mdio_write((&uni_phy)[param_1],0x11,0);
  }
  gephy_flag = 1;
  return;
}

