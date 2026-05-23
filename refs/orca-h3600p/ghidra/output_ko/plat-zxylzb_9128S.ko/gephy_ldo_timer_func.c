// module: plat-zxylzb_9128S.ko
// function: gephy_ldo_timer_func @ 0x136c8
// size: 1920 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void gephy_ldo_timer_func(void)

{
  undefined1 uVar1;
  char cVar2;
  ushort uVar3;
  uint uVar4;
  byte bVar5;
  undefined1 *puVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  byte *pbVar10;
  char *pcVar11;
  byte *pbVar12;
  ushort *puVar13;
  undefined1 *puVar14;
  bool bVar15;
  undefined1 *local_4c;
  int local_44;
  ushort local_38 [4];
  ushort local_30 [6];
  
  puVar6 = &uni_phy;
  if (gephy_flag != '\0') {
    iVar9 = temp_ctrl_read();
    if (_DAT_f0807004 != 0 || _DAT_f0807000 != 0) {
      pcVar8 = (char *)&LdoCfgFlag2;
      pcVar11 = (char *)&LdoCfgFlag1;
      if (0x32 < iVar9) goto LAB_00013c68;
      do {
        if (*pcVar11 == '\x01') {
          uVar1 = *puVar6;
          *pcVar11 = '\0';
          *pcVar8 = '\x01';
          zx_mdio_write(uVar1,0x10,0xb640);
          zx_mdio_write(*puVar6,0x11,0x1f);
        }
        while( true ) {
          pcVar11 = pcVar11 + 1;
          pcVar8 = pcVar8 + 1;
          puVar6 = puVar6 + 1;
          if (pcVar11 == (char *)&LdoCfgFlag2) goto LAB_000136e4;
          if (iVar9 < 0x33) break;
LAB_00013c68:
          if ((0x3b < iVar9) && (*pcVar8 == '\x01')) {
            uVar1 = *puVar6;
            *pcVar11 = '\x01';
            *pcVar8 = '\0';
            zx_mdio_write(uVar1,0x10,0xb640);
            zx_mdio_write(*puVar6,0x11,0x1c);
          }
        }
      } while( true );
    }
    pcVar11 = (char *)&LdoCfgFlag1;
    pcVar8 = (char *)&LdoCfgFlag2;
    if (0x32 < iVar9) goto LAB_00013bac;
    do {
      if (*pcVar11 == '\x01') {
        zx_mdio_write(*puVar6,0x10,0xb640);
        zx_mdio_write(*puVar6,0x11,0x1f);
        *pcVar8 = '\x01';
        *pcVar11 = '\0';
      }
      while( true ) {
        puVar6 = puVar6 + 1;
        pcVar11 = pcVar11 + 1;
        pcVar8 = pcVar8 + 1;
        if (puVar6 == &DAT_00021d48) goto LAB_000136e4;
        if (iVar9 < 0x33) break;
LAB_00013bac:
        if ((0x3b < iVar9) && (*pcVar8 == '\x01')) {
          zx_mdio_write(*puVar6,0x10,0xb640);
          zx_mdio_write(*puVar6,0x11,0x1c);
          *pcVar11 = '\x01';
          *pcVar8 = '\0';
        }
      }
    } while( true );
  }
LAB_000136e4:
  if (g_phy_avoid_button != '\0') {
    pcVar8 = (char *)&g_geInitFlag;
    uVar7 = 0;
    pcVar11 = (char *)&g_portEnStatus;
    do {
      if (((*pcVar11 == '\x01') && (*pcVar8 == '\x01')) &&
         (*(char *)((int)&g_geLdoFlag + uVar7) == '\x01')) {
        gephy_tx_dac_drv_force_enable(uVar7 & 0xff,0);
        *pcVar8 = '\0';
      }
      uVar7 = uVar7 + 1;
      pcVar8 = pcVar8 + 1;
      pcVar11 = pcVar11 + 1;
    } while (uVar7 != 4);
    puVar14 = g_no_cable_cnt;
    puVar6 = &uni_phy;
    pcVar8 = (char *)&g_phyPwrdnFlag;
    pcVar11 = (char *)&g_txNoForceFlag;
    uVar7 = 0;
    local_4c = &uni_phy;
    do {
      uVar4 = zx_mdio_read(*puVar6,5);
      if ((uVar4 & 0x60) == 0) {
        iVar9 = 3;
      }
      else {
        iVar9 = 0;
      }
      if ((uVar4 & 0x180) != 0) {
        iVar9 = 1;
      }
      uVar4 = zx_mdio_read(*puVar6,10);
      if ((uVar4 & 0xc00) == 0) {
        if (g_phy_dbg_lvl != '\0') goto LAB_00013e0c;
LAB_0001396c:
        if (((iVar9 != 3) || (*(char *)((int)&g_portEnStatus + uVar7) != '\x01')) ||
           (*(char *)((int)&g_linkStatus + uVar7) != '\0')) goto LAB_000137c4;
        uVar4 = *(uint *)puVar14;
        if (*pcVar11 == '\0') {
          uVar4 = uVar4 + 1;
          *(uint *)puVar14 = uVar4;
        }
      }
      else {
        if (g_phy_dbg_lvl != '\0') {
          iVar9 = 2;
LAB_00013e0c:
          printk("DEBUG:gephy link partner ability mac:%u speed:%s\n",uVar7,
                 *(undefined4 *)(&phy_speed + iVar9 * 4));
          goto LAB_0001396c;
        }
LAB_000137c4:
        uVar4 = *(uint *)puVar14;
      }
      if ((4 < uVar4) && (*(char *)((int)&no_cable_en + uVar7) == '\0')) {
        bVar15 = g_phy_dbg_lvl != '\0';
        *(undefined1 *)((int)&gephy_reneg_cnt + uVar7) = 0;
        *(undefined1 *)((int)&g_reAutoNegTimes + uVar7) = 0;
        *(undefined1 *)((int)&no_cable_en + uVar7) = 1;
        if (bVar15) {
          printk("DEBUG:Port[%u] LinkStatus:%u no cable cnt:%u,reneg cnt:%u\n",uVar7,
                 *(undefined1 *)((int)&g_linkStatus + uVar7),uVar4,0);
        }
      }
      iVar9 = zx_mdio_read(*puVar6,0);
      if ((*(uint *)puVar14 < 0x1e) || (*pcVar11 != '\0')) {
        if ((iVar9 << 0x14 < 0) && (*pcVar8 == '\0')) {
          gephy_tx_dac_drv_force_enable(uVar7 & 0xff);
          bVar15 = g_phy_dbg_lvl != '\0';
          *pcVar8 = '\x01';
          if (bVar15) {
            printk("DEBUG:Port[%u] Powerdown and txDacTxDrvNoForce:%u\n",uVar7);
          }
        }
      }
      else {
        gephy_tx_dac_drv_force_enable(uVar7 & 0xff);
        cVar2 = g_phy_dbg_lvl;
        *pcVar11 = '\x01';
        if (cVar2 != '\0') {
          printk("DEBUG:Port[%u] no cable cnt:%u txDacTxDrvNoForce Flag:%u\n",uVar7,*(uint *)puVar14
                );
        }
      }
      uVar7 = uVar7 + 1;
      puVar6 = puVar6 + 1;
      puVar14 = (undefined1 *)((int)puVar14 + 4);
      pcVar8 = pcVar8 + 1;
      pcVar11 = pcVar11 + 1;
    } while (uVar7 != 4);
    pbVar10 = (byte *)&g_reAutoNegTimes;
    pbVar12 = (byte *)&g_noerr_times;
    puVar13 = local_38;
    puVar6 = &uni_phy;
    uVar7 = 0;
    local_30[0] = 0;
    local_30[1] = 0;
    local_30[2] = 0;
    local_30[3] = 0;
    do {
      zx_mdio_read(*puVar6,0x1a);
      (*_request_threaded_irq)(0x1a36e);
      iVar9 = zx_mdio_read(*puVar6,0x1a);
      if (*pbVar10 < 0x14) {
        bVar5 = *pbVar12;
        if (*(char *)((int)&g_linkStatus + uVar7) != '\x01') goto LAB_000138cc;
        bVar15 = bVar5 == 0x1d;
        if (bVar5 < 0x1e) {
          bVar15 = (uint)(iVar9 << 0x16) >> 0x1e == 2;
        }
        if (!bVar15) goto LAB_000138cc;
        if (*(char *)((int)&g_geLdoFlag + uVar7) == '\x01') {
          uVar3 = zx_mdio_read(*puVar6,10);
          uVar1 = *puVar6;
          local_30[uVar7] = uVar3 & 0xff;
          uVar3 = zx_mdio_read(uVar1,0x14);
          *puVar13 = uVar3;
          iVar9 = *(int *)(npp_base + uVar7 * 0x40000 + 0x40788);
          uVar4 = (uint)local_30[uVar7];
          if ((uVar4 < g_idle_err_th) && (uVar3 == 0)) {
            if (uVar4 == 0) {
LAB_00013a78:
              local_44 = uVar7 << 2;
              bVar5 = *pbVar12 + 1;
              *pbVar12 = bVar5;
            }
            else {
              local_44 = uVar7 << 2;
              bVar5 = *pbVar12;
            }
          }
          else {
            local_44 = uVar7 * 4;
            if ((iVar9 == 0) || (iVar9 == *(int *)(g_smac_oct_g + uVar7 * 4))) {
              gephy_tx_dac_drv_force_enable(uVar7 & 0xff,1);
              uVar1 = *puVar6;
              *pbVar10 = *pbVar10 + 1;
              zx_mdio_write(uVar1,0,0x1340);
              cVar2 = g_phy_dbg_lvl;
              *pbVar12 = 0;
              bVar5 = 0;
              if (cVar2 != '\0') {
                printk("Err:GE %u have idle err:%u,data err:%u,oct:%u,g_oct:%u restart auto-neg times:%u\n"
                       ,uVar7,uVar4,*puVar13,iVar9,*(undefined4 *)(g_smac_oct_g + local_44),*pbVar10
                      );
                bVar5 = *pbVar12;
              }
            }
            else {
              if ((uVar4 == 0) && (*puVar13 == 0)) goto LAB_00013a78;
              bVar5 = *pbVar12;
            }
          }
          *(int *)(g_smac_oct_g + local_44) = iVar9;
          goto LAB_000138cc;
        }
      }
      else {
        bVar5 = *pbVar12;
LAB_000138cc:
        if (bVar5 == 0x1e) {
          *pbVar10 = 0;
        }
      }
      uVar7 = uVar7 + 1;
      puVar6 = puVar6 + 1;
      pbVar10 = pbVar10 + 1;
      pbVar12 = pbVar12 + 1;
      puVar13 = puVar13 + 1;
    } while (uVar7 != 4);
    uVar7 = 0;
    pcVar8 = (char *)&g_speed_action_flag;
    pbVar10 = (byte *)&g_speed_un_ge_cnt;
    pcVar11 = (char *)&g_linkStatus;
    do {
      zx_mdio_read(*local_4c,0x1a);
      iVar9 = zx_mdio_read(*local_4c,0x1a);
      uVar4 = (uint)(iVar9 << 0x16) >> 0x1e;
      bVar15 = uVar4 == 1;
      if (uVar4 < 2) {
        bVar15 = *pcVar11 == '\x01';
      }
      bVar5 = *pbVar10;
      if ((bVar15) && (bVar5 < 0x1e)) {
        bVar5 = bVar5 + 1;
        *pbVar10 = bVar5;
      }
      pbVar10 = pbVar10 + 1;
      if ((bVar5 == 0x1e) && (*pcVar8 == '\0')) {
        gephy_tx_dac_drv_force_enable(uVar7 & 0xff);
        cVar2 = g_phy_dbg_lvl;
        *pcVar8 = '\x01';
        if (cVar2 != '\0') {
          printk("DEBUG:Port[%u] link no ge and txDacDrvNoForce:%s\n",uVar7,
                 *(undefined4 *)(&phy_speed + uVar4 * 4));
        }
      }
      uVar7 = uVar7 + 1;
      pcVar8 = pcVar8 + 1;
      local_4c = local_4c + 1;
      pcVar11 = pcVar11 + 1;
    } while (uVar7 != 4);
  }
  gephy_ldo_timer._8_4_ = jiffies + 200;
  add_timer(gephy_ldo_timer);
  return;
}

