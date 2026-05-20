// module: mt7915.ko
// function: BuildMessageM8 @ 0x1f6484
// size: 1920 bytes
//

size_t BuildMessageM8(int param_1,int param_2,void *param_3)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  size_t sVar4;
  int iVar5;
  int iVar6;
  void *pvVar7;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int extraout_r1_02;
  int extraout_r1_03;
  int extraout_r1_04;
  int extraout_r1_05;
  int extraout_r1_06;
  int extraout_r1_07;
  int extraout_r1_08;
  int iVar8;
  uint __n;
  uint *puVar9;
  undefined4 *puVar10;
  size_t __n_00;
  undefined8 uVar11;
  ushort local_64;
  ushort local_62;
  undefined1 *local_60;
  size_t local_5c;
  void *local_58;
  int local_54;
  void *local_50;
  int local_4c;
  undefined1 auStack_48 [36];
  
  iVar8 = 0;
  bVar1 = *(byte *)(param_2 + 0x1c54);
  local_60 = (undefined1 *)0x0;
  local_5c = 0;
  local_54 = 0;
  local_50 = (void *)0x0;
  local_64 = 0;
  local_62 = 0;
  local_58 = param_3;
  os_alloc_mem(0,&local_54,0x200);
  if (local_54 == 0) {
    return 0;
  }
  os_alloc_mem(0,&local_60,0x400);
  iVar5 = extraout_r1;
  if ((local_60 == (undefined1 *)0x0) ||
     (os_alloc_mem(0,&local_50,0x200), iVar5 = extraout_r1_00, local_50 == (void *)0x0)) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","BuildMessageM8");
      iVar5 = extraout_r1_05;
    }
    goto LAB_001f67cc;
  }
  if (*(char *)(param_1 + 0x286285) != '\x01') {
    if (*(char *)(param_1 + 0x286285) == '\0') {
      iVar8 = 2;
    }
    else {
      iVar8 = 0xff;
    }
  }
  iVar5 = AppendWSCTLV(0x104a,local_58,param_2 + 0x70,0);
  local_58 = (void *)((int)local_58 + iVar5);
  local_5c = local_5c + iVar5;
  *local_60 = 0xc;
  iVar5 = AppendWSCTLV(0x1022,local_58,local_60,0);
  local_58 = (void *)((int)local_58 + iVar5);
  local_5c = local_5c + iVar5;
  iVar5 = AppendWSCTLV(0x101a,local_58,param_2 + 0x1b40,0);
  local_58 = (void *)((int)local_58 + iVar5);
  local_5c = local_5c + iVar5;
  if (iVar8 == 0) {
    if ((*(char *)(param_1 + 0xa7cbf9) == '\x01') || (-1 < *(char *)(param_2 + 0x355))) {
      WscCreateProfileFromCfg(param_1,0x40,param_2,param_2 + 0x1c90);
      puVar9 = (uint *)(
                       "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                       + (bVar1 & 0xf) * 0x5834 + param_1 + 8);
    }
    else {
      iVar5 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              + (*(byte *)(param_2 + 0x1c54) & 0xf) * 0x5834 + param_1 + 0xe0);
      puVar10 = *(undefined4 **)(param_1 + (int)("mt_cmd_get_sta_tx_statistic" + iVar5) * 4);
      if (puVar10 == (undefined4 *)0x0) goto LAB_001f67cc;
      if (2 < DebugLevel) {
        printk("band_idx %d  bh_bss_wdev [%s]\n",iVar5,*puVar10);
      }
      *(undefined1 *)(puVar10 + 0x4bb) = 2;
      puVar9 = puVar10 + 0xbdf;
      *(undefined4 *)((int)puVar10 + 0x2f39) = *(undefined4 *)(param_2 + 0x1c55);
      *(undefined2 *)((int)puVar10 + 0x2f3d) = *(undefined2 *)(param_2 + 0x1c59);
      WscCreateProfileFromCfg(param_1,0x40,puVar10 + 0x4b9,puVar10 + 0xbdd);
    }
LAB_001f6634:
    uVar11 = AppendWSCTLV(0x1026,local_60,&_LC25,0);
    iVar5 = (int)((ulonglong)uVar11 >> 0x20);
    if (puVar9 != (uint *)0x0) {
      uVar2 = (ushort)puVar9[9];
      uVar3 = *(ushort *)((int)puVar9 + 0x26);
      if (uVar2 == 0x22) {
        local_64 = 0x2000;
      }
      else {
        local_64 = uVar2 << 8 | uVar2 >> 8;
      }
      if (uVar3 == 0xc) {
        local_62 = 0x800;
      }
      else {
        local_62 = uVar3 << 8 | uVar3 >> 8;
      }
      iVar5 = AppendWSCTLV(0x1045,local_60 + (int)uVar11,puVar9 + 1,*puVar9 & 0xffff);
      iVar5 = (int)uVar11 + iVar5;
      iVar6 = AppendWSCTLV(0x1003,local_60 + iVar5,&local_64,0);
      iVar6 = iVar6 + iVar5;
      iVar5 = AppendWSCTLV(0x100f,local_60 + iVar6,&local_62,0);
      iVar5 = iVar5 + iVar6;
      iVar6 = AppendWSCTLV(0x1028,local_60 + iVar5,puVar9 + 0x1c,0);
      iVar6 = iVar6 + iVar5;
      iVar5 = AppendWSCTLV(0x1027,local_60 + iVar6,puVar9 + 10,(short)puVar9[0x1a]);
      iVar5 = iVar5 + iVar6;
      iVar6 = AppendWSCTLV(0x1020,local_60 + iVar5,(char *)((int)puVar9 + 0x6a),0);
      __n = iVar6 + iVar5;
      if (iVar8 == 2) {
        if (s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] != '\x01') {
          if (s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] != '\0') goto LAB_001f6758;
          goto LAB_001f6a18;
        }
        memmove(local_50,local_60,__n);
LAB_001f6760:
        RT_HMAC_SHA256(param_2 + 0x1aed,0x20,local_50,__n,local_60,0x20);
        iVar8 = AppendWSCTLV(0x101e,(int)local_50 + __n,local_60,0);
        if ((int)(iVar8 + __n) < 0x201) {
          local_4c = 0x1f0;
          AES_CBC_Encrypt(local_50,iVar8 + __n,param_2 + 0x1b0d,0x10,local_54,0x10,local_54 + 0x10,
                          &local_4c);
          iVar8 = AppendWSCTLV(0x1018,local_58,local_54,local_4c + 0x10U & 0xffff);
          local_58 = (void *)((int)local_58 + iVar8);
          local_5c = iVar8 + local_5c;
          if (((*(char *)(param_2 + 0x2b31) != '\0') &&
              (WscGenV2Msg(param_2,0,0,0,&local_58,&local_5c), *(int *)(param_2 + 0x2b28) != 0)) &&
             (*(short *)(param_2 + 0x2b26) != 0)) {
            iVar8 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_58);
            local_58 = (void *)((int)local_58 + iVar8);
            local_5c = iVar8 + local_5c;
          }
          sVar4 = local_5c;
          __n_00 = *(size_t *)(param_2 + 0x12e0);
          if (*(void **)(param_1 + 0xa77c3c) != (void *)0x0) {
            pvVar7 = memmove(*(void **)(param_1 + 0xa77c3c),(void *)(param_2 + 0x12e4),__n_00);
            memmove((void *)((int)pvVar7 + *(int *)(param_2 + 0x12e0)),param_3,local_5c);
            RT_HMAC_SHA256(param_2 + 0x1aed,0x20,*(undefined4 *)(param_1 + 0xa77c3c),__n_00 + sVar4,
                           auStack_48,0x20);
          }
          uVar11 = AppendWSCTLV(0x1005,local_58,auStack_48,0);
          iVar5 = (int)((ulonglong)uVar11 >> 0x20);
          local_58 = (void *)((int)local_58 + (int)uVar11);
          local_5c = local_5c + (int)uVar11;
          goto LAB_001f67cc;
        }
      }
      else {
        if (iVar8 != 0) {
LAB_001f6758:
          __n = 0;
          goto LAB_001f6760;
        }
LAB_001f6a18:
        __n = AppendWSCTLV(0x100e,local_50,local_60,__n & 0xffff);
        if ((int)__n < 0x201) goto LAB_001f6760;
      }
      os_free_mem(local_50);
      local_50 = (void *)0x0;
      iVar5 = extraout_r1_01;
      if (-1 < DebugLevel) {
        printk("%s: Plain buf overflow!!!\n","BuildMessageM8");
        iVar5 = extraout_r1_08;
      }
      goto LAB_001f67cc;
    }
  }
  else {
    if (iVar8 == 2) {
      if ((*(int *)(&DAT_00370acc + param_1) == 0) ||
         ((s_start___>__s_003715c4[param_1] != '\0' &&
          (((*(char *)(param_2 + 0x2b32) == '\0' || (*(char *)(param_2 + 0x2b31) == '\0')) ||
           (*(char *)(param_2 + 0x1e5) == '\0')))))) {
        WscCreateProfileFromCfg(param_1,2,param_2,param_2 + 0x1c90);
      }
      puVar9 = (uint *)(&DAT_00370ad4 + param_1);
      *(undefined4 *)(&DAT_00370b3e + param_1) = *(undefined4 *)(&DAT_00371c92 + param_1);
      *(undefined2 *)(&DAT_00370b42 + param_1) = *(undefined2 *)(&DAT_00371c96 + param_1);
      goto LAB_001f6634;
    }
    AppendWSCTLV(0x1026,local_60,&_LC25,0);
    iVar5 = extraout_r1_06;
  }
  if (-1 < DebugLevel) {
    printk("%s: pWscControl == NULL!\n","BuildMessageM8");
    iVar5 = extraout_r1_07;
  }
LAB_001f67cc:
  if (local_54 != 0) {
    os_free_mem();
    iVar5 = extraout_r1_02;
  }
  *(undefined1 *)(param_2 + 0x1c53) = 0;
  if (local_60 != (undefined1 *)0x0) {
    os_free_mem();
    iVar5 = extraout_r1_03;
  }
  if (local_50 != (void *)0x0) {
    os_free_mem();
    iVar5 = extraout_r1_04;
  }
  if (2 < DebugLevel) {
    printk("BuildMessageM8 :\n",iVar5);
  }
  return local_5c;
}

