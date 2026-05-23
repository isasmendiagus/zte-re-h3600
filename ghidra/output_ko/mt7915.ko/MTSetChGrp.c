// module: mt7915.ko
// function: MTSetChGrp @ 0x141660
// size: 900 bytes
//

void MTSetChGrp(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  char cVar3;
  char *__s;
  int iVar4;
  size_t sVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  char cVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  char *local_38;
  char *local_2c [2];
  
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    local_38 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + param_1 + 0xe0;
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    local_38 = &DAT_0036db58 + param_1;
  }
  else {
    local_38 = (char *)0x0;
  }
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("[MTSetChGrp] (buf == NULL) Not enough memory for dynamic allocating\n");
    }
  }
  else {
    __s = (char *)rstrtok(param_2,&_LC3);
    if (__s != (char *)0x0) {
      cVar9 = '\0';
      do {
        if (*(int *)(param_1 + 0x795050) == 2) {
          iVar4 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),cVar9);
          if (0 < DebugLevel) {
            printk("[MTSetChGrp] ENUM_DBDC_5G5G: BandIdx = %d\n",cVar9);
          }
        }
        else if ((local_38 == (char *)0x0) || ((*(ushort *)(local_38 + 0x18) & 0xb1) == 0)) {
          iVar4 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),cVar9);
        }
        else if ((cVar9 == '\0') && (*(char *)(param_1 + 0x79504d) == '\x01')) {
          iVar4 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
        }
        else {
          iVar4 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),0);
        }
        uVar11 = 0;
        __memzero(iVar4 + 0x49e,0x3b);
        *(undefined1 *)(iVar4 + 0x4d9) = 0;
        *(undefined1 *)(iVar4 + 0x49d) = 0;
        sVar5 = strlen(__s);
        uVar12 = sVar5 + 1 & 0xff;
        os_alloc_mem(0,local_2c,uVar12);
        if (local_2c[0] == (char *)0x0) {
          if (DebugLevel < 0) {
            return;
          }
          printk("[MTSetChGrp] (buf_ChGrp == NULL) Not enough memory for dynamic allocating\n");
          return;
        }
        strncpy(local_2c[0],__s,uVar12);
        iVar6 = rstrtok(local_2c[0],&_LC6);
        if (iVar6 == 0) {
          uVar11 = 0;
        }
        else {
          uVar10 = 0;
          do {
            cVar3 = simple_strtol(iVar6,0,10);
            if (cVar3 == '\x01') {
              iVar6 = uVar10 * 2;
              bVar1 = Channel_GRP[iVar6 + 1];
              uVar7 = uVar11 + bVar1;
              if (uVar7 < 0x3b) {
                *(byte *)(iVar4 + 0x49d) = *(byte *)(iVar4 + 0x49d) | (byte)(1 << uVar10);
                if (bVar1 != 0) {
                  uVar7 = 0;
                  do {
                    iVar2 = DebugLevel;
                    uVar8 = uVar11 + uVar7;
                    if (uVar8 < 0x3b) {
                      bVar1 = Channel_GRP[iVar6];
                      *(byte *)(iVar4 + uVar8 + 0x49e) = bVar1 + (char)uVar7 * '\x04';
                      if (2 < iVar2) {
                        printk("[MTSetChGrp] Test - ChCtrl[%d]->ChGrpABandChList[%d]=%d\n",cVar9,
                               uVar8,uVar7 * 4 + (uint)bVar1);
                      }
                    }
                    uVar7 = uVar7 + 1 & 0xff;
                  } while (uVar7 < (byte)Channel_GRP[iVar6 + 1]);
                  uVar7 = uVar11 + (byte)Channel_GRP[iVar6 + 1];
                }
                uVar11 = uVar7 & 0xff;
              }
            }
            iVar6 = rstrtok(0,&_LC6);
            uVar10 = uVar10 + 1 & 0xff;
          } while (uVar10 < 5 && iVar6 != 0);
        }
        iVar6 = DebugLevel;
        param_2 = param_2 + uVar12 + 1;
        *(char *)(iVar4 + 0x4d9) = (char)uVar11;
        if (2 < iVar6) {
          uVar12 = (uint)*(byte *)(iVar4 + 0x49d);
          printk("[MTSetChGrp] BandIdx =%d, pChCtrl->ChGrpABandChNum=%d, ChGrp=%d/%d/%d/%d\n",cVar9,
                 uVar11,uVar12 & 1,(uVar12 << 0x1e) >> 0x1f,(uVar12 << 0x1d) >> 0x1f,
                 (uVar12 << 0x1c) >> 0x1f);
        }
        cVar9 = cVar9 + '\x01';
        os_free_mem(local_2c[0]);
        __s = (char *)rstrtok(param_2,&_LC3);
      } while (__s != (char *)0x0);
    }
  }
  return;
}

