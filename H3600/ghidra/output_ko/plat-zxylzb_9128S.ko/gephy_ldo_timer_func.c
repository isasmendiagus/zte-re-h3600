// module: plat-zxylzb_9128S.ko
// function: gephy_ldo_timer_func @ 0x13784
// size: 1872 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void gephy_ldo_timer_func(void)

{
  undefined1 uVar1;
  char cVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  byte bVar6;
  undefined1 *puVar7;
  uint uVar8;
  char *pcVar9;
  byte *pbVar10;
  char *pcVar11;
  byte *pbVar12;
  ushort *puVar13;
  undefined1 *puVar14;
  int iVar15;
  bool bVar16;
  undefined1 *local_4c;
  int local_44;
  ushort local_38 [4];
  ushort local_30 [6];
  
  puVar7 = &uni_phy;
  if (gephy_flag != '\0') {
    iVar15 = temp_ctrl_read();
    if (_DAT_f0807004 != 0 || _DAT_f0807000 != 0) {
      pcVar9 = (char *)&LdoCfgFlag2;
      pcVar11 = (char *)&LdoCfgFlag1;
      if (0x32 < iVar15) goto LAB_00013d00;
      do {
        if (*pcVar11 == '\x01') {
          uVar1 = *puVar7;
          *pcVar11 = '\0';
          *pcVar9 = '\x01';
          zx_mdio_write(uVar1,0x10,0xb640);
          zx_mdio_write(*puVar7,0x11,0x1f);
        }
        while( true ) {
          pcVar11 = pcVar11 + 1;
          pcVar9 = pcVar9 + 1;
          puVar7 = puVar7 + 1;
          if (pcVar11 == (char *)&LdoCfgFlag2) goto LAB_000137a0;
          if (iVar15 < 0x33) break;
LAB_00013d00:
          if ((0x3b < iVar15) && (*pcVar9 == '\x01')) {
            uVar1 = *puVar7;
            *pcVar11 = '\x01';
            *pcVar9 = '\0';
            zx_mdio_write(uVar1,0x10,0xb640);
            zx_mdio_write(*puVar7,0x11,0x1c);
          }
        }
      } while( true );
    }
    pcVar11 = (char *)&LdoCfgFlag1;
    pcVar9 = (char *)&LdoCfgFlag2;
    if (0x32 < iVar15) goto LAB_00013c44;
    do {
      if (*pcVar11 == '\x01') {
        zx_mdio_write(*puVar7,0x10,0xb640);
        zx_mdio_write(*puVar7,0x11,0x1f);
        *pcVar9 = '\x01';
        *pcVar11 = '\0';
      }
      while( true ) {
        puVar7 = puVar7 + 1;
        pcVar11 = pcVar11 + 1;
        pcVar9 = pcVar9 + 1;
        if (puVar7 == &DAT_000216ec) goto LAB_000137a0;
        if (iVar15 < 0x33) break;
LAB_00013c44:
        if ((0x3b < iVar15) && (*pcVar9 == '\x01')) {
          zx_mdio_write(*puVar7,0x10,0xb640);
          zx_mdio_write(*puVar7,0x11,0x1c);
          *pcVar11 = '\x01';
          *pcVar9 = '\0';
        }
      }
    } while( true );
  }
LAB_000137a0:
  if (g_phy_avoid_button != '\0') {
    pcVar9 = (char *)&g_geInitFlag;
    uVar8 = 0;
    pcVar11 = (char *)&g_portEnStatus;
    do {
      if (((*pcVar11 == '\x01') && (*pcVar9 == '\x01')) &&
         (*(char *)((int)&g_geLdoFlag + uVar8) == '\x01')) {
        gephy_tx_dac_drv_force_enable(uVar8 & 0xff,0);
        *pcVar9 = '\0';
      }
      uVar8 = uVar8 + 1;
      pcVar9 = pcVar9 + 1;
      pcVar11 = pcVar11 + 1;
    } while (uVar8 != 4);
    puVar14 = g_no_cable_cnt;
    puVar7 = &uni_phy;
    pcVar9 = (char *)&g_phyPwrdnFlag;
    pcVar11 = (char *)&g_txNoForceFlag;
    uVar8 = 0;
    local_4c = &uni_phy;
    do {
      uVar5 = zx_mdio_read(*puVar7,5);
      if ((uVar5 & 0x60) == 0) {
        iVar15 = 3;
      }
      else {
        iVar15 = 0;
      }
      if ((uVar5 & 0x180) != 0) {
        iVar15 = 1;
      }
      uVar5 = zx_mdio_read(*puVar7,10);
      if ((uVar5 & 0xc00) == 0) {
        if (g_phy_dbg_lvl != '\0') goto LAB_00013e98;
LAB_00013a28:
        if (((iVar15 != 3) || (*(char *)((int)&g_portEnStatus + uVar8) != '\x01')) ||
           (*(char *)((int)&g_linkStatus + uVar8) != '\0')) goto LAB_00013880;
        uVar5 = *(uint *)puVar14;
        if (*pcVar11 == '\0') {
          uVar5 = uVar5 + 1;
          *(uint *)puVar14 = uVar5;
        }
      }
      else {
        if (g_phy_dbg_lvl != '\0') {
          iVar15 = 2;
LAB_00013e98:
          printk("DEBUG:gephy link partner ability mac:%u speed:%s\n",uVar8,(&phy_speed)[iVar15]);
          goto LAB_00013a28;
        }
LAB_00013880:
        uVar5 = *(uint *)puVar14;
      }
      if ((4 < uVar5) && (*(char *)((int)&no_cable_en + uVar8) == '\0')) {
        bVar16 = g_phy_dbg_lvl != '\0';
        *(undefined1 *)((int)&gephy_reneg_cnt + uVar8) = 0;
        *(undefined1 *)((int)&g_reAutoNegTimes + uVar8) = 0;
        *(undefined1 *)((int)&no_cable_en + uVar8) = 1;
        if (bVar16) {
          printk("DEBUG:Port[%u] LinkStatus:%u no cable cnt:%u,reneg cnt:%u\n",uVar8,
                 *(undefined1 *)((int)&g_linkStatus + uVar8),uVar5,0);
        }
      }
      iVar15 = zx_mdio_read(*puVar7,0);
      if ((*(uint *)puVar14 < 0x1e) || (*pcVar11 != '\0')) {
        if ((iVar15 << 0x14 < 0) && (*pcVar9 == '\0')) {
          gephy_tx_dac_drv_force_enable(uVar8 & 0xff);
          bVar16 = g_phy_dbg_lvl != '\0';
          *pcVar9 = '\x01';
          if (bVar16) {
            printk("DEBUG:Port[%u] Powerdown and txDacTxDrvNoForce:%u\n",uVar8);
          }
        }
      }
      else {
        gephy_tx_dac_drv_force_enable(uVar8 & 0xff);
        cVar2 = g_phy_dbg_lvl;
        *pcVar11 = '\x01';
        if (cVar2 != '\0') {
          printk("DEBUG:Port[%u] no cable cnt:%u txDacTxDrvNoForce Flag:%u\n",uVar8,*(uint *)puVar14
                );
        }
      }
      uVar8 = uVar8 + 1;
      puVar7 = puVar7 + 1;
      puVar14 = (undefined1 *)((int)puVar14 + 4);
      pcVar9 = pcVar9 + 1;
      pcVar11 = pcVar11 + 1;
    } while (uVar8 != 4);
    pbVar12 = (byte *)&g_noerr_times;
    puVar13 = local_38;
    uVar8 = 0;
    puVar7 = &uni_phy;
    local_30[0] = 0;
    local_30[1] = 0;
    local_30[2] = 0;
    local_30[3] = 0;
    pbVar10 = (byte *)&g_reAutoNegTimes;
    do {
      zx_mdio_read(*puVar7,0x1a);
      (*_request_threaded_irq)(0x1a36e);
      iVar15 = zx_mdio_read(*puVar7,0x1a);
      if (*pbVar10 < 0x14) {
        bVar6 = *pbVar12;
        if (*(char *)((int)&g_linkStatus + uVar8) == '\x01') {
          bVar16 = bVar6 == 0x1d;
          if (bVar6 < 0x1e) {
            bVar16 = (uint)(iVar15 << 0x16) >> 0x1e == 2;
          }
          if (bVar16) {
            uVar3 = zx_mdio_read(*puVar7,10);
            uVar1 = *puVar7;
            local_30[uVar8] = uVar3 & 0xff;
            uVar4 = zx_mdio_read(uVar1,0x14);
            *puVar13 = uVar4;
            iVar15 = *(int *)(npp_base + uVar8 * 0x40000 + 0x40788);
            uVar3 = local_30[uVar8];
            if ((uVar3 == 0) && (uVar4 == 0)) {
LAB_00013b10:
              bVar6 = *pbVar12 + 1;
              *pbVar12 = bVar6;
            }
            else if ((iVar15 == 0) || (iVar15 == *(int *)(g_smac_oct_g + uVar8 * 4))) {
              local_44 = uVar8 * 4;
              gephy_tx_dac_drv_force_enable(uVar8 & 0xff,1);
              uVar1 = *puVar7;
              *pbVar10 = *pbVar10 + 1;
              zx_mdio_write(uVar1,0,0x1340);
              cVar2 = g_phy_dbg_lvl;
              *pbVar12 = 0;
              bVar6 = 0;
              if (cVar2 != '\0') {
                printk("Err:GE %u have idle err:%u,data err:%u,oct:%u,g_oct:%u restart auto-neg times:%u\n"
                       ,uVar8,uVar3,*puVar13,iVar15,*(undefined4 *)(g_smac_oct_g + local_44),
                       *pbVar10);
                bVar6 = *pbVar12;
              }
            }
            else {
              if ((uVar3 == 0) && (*puVar13 == 0)) goto LAB_00013b10;
              bVar6 = *pbVar12;
            }
            local_44 = uVar8 * 4;
            *(int *)(g_smac_oct_g + local_44) = iVar15;
          }
        }
      }
      else {
        bVar6 = *pbVar12;
      }
      uVar8 = uVar8 + 1;
      puVar7 = puVar7 + 1;
      if (bVar6 == 0x1e) {
        *pbVar10 = 0;
      }
      pbVar12 = pbVar12 + 1;
      puVar13 = puVar13 + 1;
      pbVar10 = pbVar10 + 1;
    } while (uVar8 != 4);
    uVar8 = 0;
    pcVar9 = (char *)&g_speed_action_flag;
    pbVar10 = (byte *)&g_speed_un_ge_cnt;
    pcVar11 = (char *)&g_linkStatus;
    do {
      zx_mdio_read(*local_4c,0x1a);
      iVar15 = zx_mdio_read(*local_4c,0x1a);
      uVar5 = (uint)(iVar15 << 0x16) >> 0x1e;
      bVar16 = uVar5 == 1;
      if (uVar5 < 2) {
        bVar16 = *pcVar11 == '\x01';
      }
      bVar6 = *pbVar10;
      if ((bVar16) && (bVar6 < 0x1e)) {
        bVar6 = bVar6 + 1;
        *pbVar10 = bVar6;
      }
      pbVar10 = pbVar10 + 1;
      if ((bVar6 == 0x1e) && (*pcVar9 == '\0')) {
        gephy_tx_dac_drv_force_enable(uVar8 & 0xff);
        cVar2 = g_phy_dbg_lvl;
        *pcVar9 = '\x01';
        if (cVar2 != '\0') {
          printk("DEBUG:Port[%u] link no ge and txDacDrvNoForce:%s\n",uVar8,(&phy_speed)[uVar5]);
        }
      }
      uVar8 = uVar8 + 1;
      pcVar9 = pcVar9 + 1;
      pcVar11 = pcVar11 + 1;
      local_4c = local_4c + 1;
    } while (uVar8 != 4);
  }
  gephy_ldo_timer._8_4_ = jiffies + 200;
  add_timer(gephy_ldo_timer);
  return;
}

