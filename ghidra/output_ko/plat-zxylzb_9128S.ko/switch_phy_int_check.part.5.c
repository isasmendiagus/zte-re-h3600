// module: plat-zxylzb_9128S.ko
// function: switch_phy_int_check.part.5 @ 0x13fb0
// size: 808 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void switch_phy_int_check_part_5(uint param_1)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  int unaff_r7;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  bool bVar12;
  
  if (param_1 < 4) {
    zx_mdio_read((&uni_phy)[param_1],0x1a);
    iVar7 = 10;
    do {
      (*_request_threaded_irq)(0x66665b0);
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    uVar6 = zx_mdio_read((&uni_phy)[param_1],0x1a);
    if ((uVar6 & 0x40) == 0) {
      printk("mac %d link down\n",param_1);
      pon_npp_smac_disable_part_4(param_1);
      *(undefined1 *)((int)&g_linkStatus + param_1) = 0;
      return;
    }
    uVar6 = uVar6 & 0x380;
    uVar8 = uVar6 >> 8;
    bVar12 = g_phy_avoid_button != '\0';
    if (!bVar12) {
      unaff_r7 = param_1 << 2;
    }
    *(undefined1 *)((int)&g_linkStatus + param_1) = 1;
    if (bVar12) {
      unaff_r7 = param_1 * 4;
      *(undefined1 *)((int)&g_noerr_times + param_1) = 0;
      *(undefined1 *)((int)&no_cable_en + param_1) = 0;
      *(undefined1 *)((int)&g_txNoForceFlag + param_1) = 0;
      *(undefined1 *)((int)&g_phyPwrdnFlag + param_1) = 0;
      *(undefined1 *)((int)&g_speed_un_ge_cnt + param_1) = 0;
      *(undefined1 *)((int)&g_speed_action_flag + param_1) = 0;
      cVar1 = *(char *)((int)&g_geLdoFlag + param_1);
      *(undefined4 *)(g_no_cable_cnt + unaff_r7) = 0;
      bVar3 = g_reneg_times;
      if (cVar1 == '\0') {
        bVar3 = 0;
      }
      if (*(int *)(g_SpeedChange + unaff_r7) == 1) {
        uVar9 = zx_mdio_read((&uni_phy)[param_1],9);
        if (((uVar8 == 1) && ((uVar9 & 0x300) != 0)) &&
           (*(byte *)((int)&gephy_reneg_cnt + param_1) < bVar3)) {
          uVar4 = 0;
          puVar5 = (undefined4 *)g_no_cable_cnt;
          puVar10 = &g_txNoForceFlag;
          do {
            uVar2 = uVar4 & 0xff;
            uVar4 = uVar4 + 1;
            gephy_tx_dac_drv_force_enable(uVar2);
            *puVar5 = 0;
            *(undefined1 *)puVar10 = 0;
            puVar5 = puVar5 + 1;
            puVar10 = (undefined4 *)((int)puVar10 + 1);
          } while (uVar4 != 4);
          *(char *)((int)&gephy_reneg_cnt + param_1) =
               *(char *)((int)&gephy_reneg_cnt + param_1) + '\x01';
          zx_mdio_write((&uni_phy)[param_1],0,0x1340);
          if (g_phy_dbg_lvl != '\0') {
            printk("%s %d mac %u own parten 0x%x speed %s re auto-neg\n","switch_phy_int_check",
                   0x568,param_1,uVar9,&_LC14);
          }
        }
        *(undefined4 *)(g_SpeedChange + unaff_r7) = 0;
      }
    }
    if (uVar6 == *(uint *)(uni_phy_stat + unaff_r7)) {
      pon_npp_smac_enable_part_3(param_1);
      return;
    }
    if (uVar8 == 3) {
      return;
    }
    uVar9 = (uVar6 << 0x18) >> 0x1f;
  }
  else {
    if (4 < param_1) {
      pon_reset(1 << (param_1 + 6 & 0xff));
      smac_init(param_1);
      unaff_r7 = param_1 << 2;
      smac_sopc_mode_switch(param_1,0);
      uVar6 = 0;
      goto LAB_00014000;
    }
    uVar9 = 0;
    unaff_r7 = param_1 << 2;
    uVar8 = 0;
    uVar6 = 0;
  }
  iVar7 = param_1 * 0x40000 + 0x40090;
  uVar11 = *(undefined4 *)(npp_base + iVar7);
  pon_reset(1 << (param_1 + 6 & 0xff));
  smac_init(param_1);
  pon_npp_smac_config_speed_duplex_part_0(param_1,uVar8,uVar9);
  smac_sopc_mode_switch(param_1,uVar9);
  pon_npp_smac_enable_part_3(param_1);
  *(undefined4 *)(npp_base + iVar7) = uVar11;
LAB_00014000:
  *(uint *)(uni_phy_stat + unaff_r7) = uVar6;
  *(int *)(g_lanPortRstMonitor + unaff_r7) = *(int *)(g_lanPortRstMonitor + unaff_r7) + 1;
  return;
}

