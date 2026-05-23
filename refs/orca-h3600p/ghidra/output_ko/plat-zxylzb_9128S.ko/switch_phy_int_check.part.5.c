// module: plat-zxylzb_9128S.ko
// function: switch_phy_int_check.part.5 @ 0x13f28
// size: 1044 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void switch_phy_int_check_part_5(uint param_1)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  bool bVar10;
  int local_3c;
  undefined4 *local_38;
  
  if (param_1 < 4) {
    zx_mdio_read((&uni_phy)[param_1],0x1a);
    iVar7 = 10;
    do {
      (*_request_threaded_irq)(0x66665b0);
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    uVar4 = zx_mdio_read((&uni_phy)[param_1],0x1a);
    if ((uVar4 & 0x40) == 0) {
      printk("mac %d link down\n",param_1);
      pon_npp_smac_disable_part_4(param_1);
      *(undefined1 *)((int)&g_linkStatus + param_1) = 0;
      return;
    }
    uVar4 = uVar4 & 0x380;
    bVar10 = g_phy_avoid_button == '\0';
    uVar5 = uVar4 >> 8;
    *(undefined1 *)((int)&g_linkStatus + param_1) = 1;
    if (bVar10) {
      local_3c = param_1 << 2;
    }
    else {
      local_3c = param_1 * 4;
      *(undefined1 *)((int)&g_noerr_times + param_1) = 0;
      *(undefined1 *)((int)&no_cable_en + param_1) = 0;
      *(undefined1 *)((int)&g_txNoForceFlag + param_1) = 0;
      *(undefined1 *)((int)&g_phyPwrdnFlag + param_1) = 0;
      *(undefined1 *)((int)&g_speed_un_ge_cnt + param_1) = 0;
      *(undefined1 *)((int)&g_speed_action_flag + param_1) = 0;
      cVar1 = *(char *)((int)&g_geLdoFlag + param_1);
      *(undefined4 *)(g_no_cable_cnt + local_3c) = 0;
      bVar3 = g_reneg_times;
      if (cVar1 == '\0') {
        bVar3 = 0;
      }
      if (*(int *)(g_SpeedChange + local_3c) == 1) {
        uVar6 = zx_mdio_read((&uni_phy)[param_1],9);
        if (((uVar5 == 1) && ((uVar6 & 0x300) != 0)) &&
           (*(byte *)((int)&gephy_reneg_cnt + param_1) < bVar3)) {
          uVar8 = 0;
          local_38 = (undefined4 *)g_no_cable_cnt;
          puVar9 = &g_txNoForceFlag;
          do {
            uVar2 = uVar8 & 0xff;
            uVar8 = uVar8 + 1;
            gephy_tx_dac_drv_force_enable(uVar2);
            *local_38 = 0;
            *(undefined1 *)puVar9 = 0;
            puVar9 = (undefined4 *)((int)puVar9 + 1);
            local_38 = local_38 + 1;
          } while (uVar8 != 4);
          *(char *)((int)&gephy_reneg_cnt + param_1) =
               *(char *)((int)&gephy_reneg_cnt + param_1) + '\x01';
          zx_mdio_write((&uni_phy)[param_1],0,0x1340);
          if (g_phy_dbg_lvl != '\0') {
            printk("%s %d mac %u own parten 0x%x speed %s re auto-neg\n","switch_phy_int_check",
                   0x577,param_1,uVar6,&_LC14);
          }
        }
        *(undefined4 *)(g_SpeedChange + local_3c) = 0;
      }
    }
    if (uVar4 == *(uint *)(uni_phy_stat + local_3c)) {
      pon_npp_smac_enable_part_3(param_1);
      return;
    }
    if (uVar5 == 3) {
      return;
    }
    uVar8 = (uVar4 << 0x18) >> 0x1f;
    uVar6 = uVar8 ^ 1;
  }
  else {
    if (4 < param_1) {
      uVar6 = 1;
      pon_reset(1 << (param_1 + 6 & 0xff));
      smac_init(param_1);
      uVar4 = 0;
      local_3c = param_1 << 2;
      local_38 = (undefined4 *)0x0;
      goto LAB_00013f84;
    }
    uVar8 = 0;
    uVar5 = 0;
    uVar4 = 0;
    uVar6 = 1;
    local_3c = param_1 << 2;
  }
  local_38 = *(undefined4 **)(npp_base + param_1 * 0x40000 + 0x40090);
  pon_reset(1 << (param_1 + 6 & 0xff));
  smac_init(param_1);
  pon_npp_smac_config_speed_duplex_part_0(param_1,uVar5,uVar8);
LAB_00013f84:
  iVar7 = 5;
  do {
    (*_request_threaded_irq)(0x66665b0);
    if ((*(uint *)(npp_base + 0x19068) & 1 << (param_1 + 5 & 0xff)) != 0) {
      *(uint *)(npp_base + 0x19068) = *(uint *)(npp_base + 0x19068) | 1 << (param_1 & 0xff);
      break;
    }
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  *(uint *)(npp_base + 0x19038) =
       *(uint *)(npp_base + 0x19038) & ~(1 << (param_1 + 0x10 & 0xff)) |
       uVar6 << (param_1 + 0x10 & 0xff);
  (*_request_threaded_irq)(0x66665b0);
  if (param_1 < 5) {
    pon_npp_smac_enable_part_3(param_1);
    *(undefined4 **)(npp_base + param_1 * 0x40000 + 0x40090) = local_38;
  }
  *(uint *)(uni_phy_stat + local_3c) = uVar4;
  *(int *)(g_lanPortRstMonitor + local_3c) = *(int *)(g_lanPortRstMonitor + local_3c) + 1;
  return;
}

