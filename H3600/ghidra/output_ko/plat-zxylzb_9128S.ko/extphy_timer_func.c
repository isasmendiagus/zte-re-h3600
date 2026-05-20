// module: plat-zxylzb_9128S.ko
// function: extphy_timer_func @ 0x14580
// size: 456 bytes
//

void extphy_timer_func(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  uVar5 = (uint)(byte)lan_up_port;
  iVar1 = uVar5 * 4;
  uVar2 = zx_mdio_read((&uni_phy)[uVar5],0x1e);
  zx_mdio_write((&uni_phy)[uVar5],0x1e,0);
  zx_mdio_read((&uni_phy)[uVar5],0x1a);
  uVar3 = zx_mdio_read((&uni_phy)[uVar5],0x1a);
  zx_mdio_write((&uni_phy)[uVar5],0x1e,uVar2);
  if ((uVar3 & 0x380) == *(uint *)(uni_phy_stat + iVar1)) {
    pon_npp_smac_enable(uVar5);
  }
  else if ((uVar3 & 0x40) == 0) {
    if (*(uint *)(uni_phy_stat + iVar1) != 0xffffffff) {
      *(undefined4 *)(uni_phy_stat + iVar1) = 0xffffffff;
      printk("mac %d link down,s %.4x\n",uVar5,uVar3);
    }
    pon_npp_smac_disable(uVar5);
  }
  else {
    uVar6 = (uVar3 << 9) >> 0x10;
    printk("status=0x%x \n",uVar3);
    uVar4 = uVar6 & 7;
    if (uVar4 < 2) {
      iVar8 = 0;
    }
    else if (uVar4 - 2 < 2) {
      iVar8 = 1;
    }
    else if (uVar4 - 4 < 2) {
      iVar8 = 2;
    }
    else {
      iVar8 = 0;
    }
    uVar6 = uVar6 & 5;
    if (uVar4 == 4 || uVar6 == 0) {
      iVar7 = 0;
    }
    else if (uVar6 == 1 || uVar4 == 5) {
      iVar7 = 1;
    }
    else {
      iVar7 = 0;
    }
    printk("mac %d phy status changed: %s %s\n",uVar5,(&phy_speed)[iVar8],
           *(undefined4 *)((int)&phy_duplex + iVar7 * 4));
    pon_reset(1 << (uVar5 + 6 & 0xff));
    smac_init(uVar5);
    pon_npp_smac_config_speed_duplex(uVar5,iVar8,iVar7);
    smac_sopc_mode_switch(uVar5,iVar7);
    pon_npp_smac_enable(uVar5);
    *(uint *)(uni_phy_stat + iVar1) = uVar3 & 0x380;
  }
  extphy_timer._8_4_ = jiffies + 10;
  add_timer(extphy_timer);
  return;
}

