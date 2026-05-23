// module: mt7915.ko
// function: ap_ampdu_tx @ 0x1bca8
// size: 2688 bytes
//

undefined4 ap_ampdu_tx(int param_1,undefined4 param_2,int param_3)

{
  undefined1 uVar1;
  char cVar2;
  byte *pbVar3;
  int iVar4;
  int *piVar5;
  void *pvVar6;
  int iVar7;
  ushort *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  byte bVar13;
  void *__dest;
  uint uVar14;
  undefined6 *__src;
  int iVar15;
  uint uVar16;
  bool bVar17;
  undefined2 local_2a [3];
  
  local_2a[0] = 1;
  pbVar3 = (byte *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar13 = *pbVar3;
  uVar16 = (uint)pbVar3[2];
  iVar4 = fill_tx_blk(param_1,param_2,param_3);
  iVar10 = *(int *)(param_3 + 0x78);
  if (iVar4 == 0) {
    if (iVar10 == 0) {
      iVar4 = *(int *)(param_3 + 0x74);
      if (iVar4 != 0) {
        *(int *)(iVar4 + 0x213194) = *(int *)(iVar4 + 0x213194) + 1;
      }
    }
    else {
      *(int *)(iVar10 + 0x43fc) = *(int *)(iVar10 + 0x43fc) + 1;
    }
    *(int *)(param_1 + 0x9db94) = *(int *)(param_1 + 0x9db94) + 1;
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
    return 1;
  }
  iVar4 = *(int *)(param_3 + 8);
  if (iVar10 != 0) {
    *(int *)(iVar10 + 0x4418) = *(int *)(iVar10 + 0x4418) + 1;
  }
  if ((*(uint *)(param_3 + 0x18) & 0x800000) != 0) {
    __dest = (void *)0x0;
    *(undefined1 *)(param_3 + 0x35) = 0;
    *(undefined1 *)(param_3 + 0x34) = 2;
    *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
    goto LAB_0001bd7c;
  }
  iVar10 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar10 != 2) {
    uVar16 = bVar13 + 4;
  }
  if (*(char *)(iVar4 + 0xc1) == '\0') {
    iVar10 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    iVar9 = *(int *)(param_3 + 0x58);
    iVar11 = *(int *)(param_3 + 0x10);
    iVar15 = *(int *)(param_3 + 8);
    uVar14 = (uint)*(byte *)(iVar10 + 2);
    *(undefined1 *)(param_3 + 0x35) = 0x18;
    iVar10 = iVar9 + uVar14;
    *(undefined1 *)(param_3 + 0x2c) = 0x18;
    *(int *)(param_3 + 0x5c) = iVar10;
    __memzero(iVar10,0x18);
    *(byte *)(iVar10 + 1) = *(byte *)(iVar10 + 1) | 2;
    bVar13 = *(byte *)(iVar9 + uVar14);
    *(byte *)(iVar9 + uVar14) = bVar13 & 0xf3 | 8;
    if ((*(uint *)(param_3 + 0x18) & 0x10) == 0) {
      cVar2 = '\0';
    }
    else {
      cVar2 = '\b';
    }
    *(byte *)(iVar9 + uVar14) = bVar13 & 3 | 8 | cVar2 << 4;
    if (iVar15 == 0) {
      puVar8 = (ushort *)(param_1 + 0xa39f90);
      *(byte *)(iVar10 + 0x16) = *(byte *)(iVar10 + 0x16) & 0xf | *(char *)(param_1 + 0xa39f90) << 4
      ;
      *(char *)(iVar10 + 0x17) = (char)(((uint)*puVar8 << 0x14) >> 0x18);
      *puVar8 = *puVar8 + 1 & 0xfff;
    }
    else if ((*(uint *)(param_3 + 0x18) & 0x10) == 0) {
      *(byte *)(iVar10 + 0x16) = *(byte *)(iVar10 + 0x16) & 0xf | *(char *)(iVar15 + 0x12) << 4;
      *(char *)(iVar10 + 0x17) = (char)(((uint)*(ushort *)(iVar15 + 0x12) << 0x14) >> 0x18);
      *(ushort *)(iVar15 + 0x12) = *(short *)(iVar15 + 0x12) + 1U & 0xfff;
    }
    else {
      iVar7 = iVar15 + (*(byte *)(param_3 + 0x1c) + 8) * 2;
      *(byte *)(iVar10 + 0x16) = *(byte *)(iVar10 + 0x16) & 0xf | *(char *)(iVar7 + 4) << 4;
      *(char *)(iVar10 + 0x17) = (char)(((uint)*(ushort *)(iVar7 + 4) << 0x14) >> 0x18);
      iVar15 = iVar15 + (uint)*(byte *)(param_3 + 0x1c) * 2;
      *(ushort *)(iVar15 + 0x14) = *(short *)(iVar15 + 0x14) + 1U & 0xfff;
    }
    *(byte *)(iVar10 + 0x16) = *(byte *)(iVar10 + 0x16) & 0xf0;
    *(byte *)(iVar10 + 1) =
         *(byte *)(iVar10 + 1) & 0xdf |
         (byte)(((uint)(*(int *)(param_3 + 0x18) << 0x19) >> 0x1f) << 5);
    if ((*(uint *)(param_3 + 0x18) & 0x8000000) == 0) {
      if ((*(uint *)(param_3 + 0x18) & 0x200) == 0) {
        if ((*(int **)(param_3 + 8) == (int *)0x0) || (**(int **)(param_3 + 8) == 0x400)) {
          puVar12 = *(undefined4 **)(param_3 + 0x24);
          *(undefined4 *)(iVar10 + 4) = *puVar12;
          *(undefined2 *)(iVar10 + 8) = *(undefined2 *)(puVar12 + 1);
        }
        else {
          iVar15 = *(int *)(param_3 + 0x14);
          *(undefined4 *)(iVar10 + 4) = *(undefined4 *)(iVar15 + 0xec);
          *(undefined2 *)(iVar10 + 8) = *(undefined2 *)(iVar15 + 0xf0);
        }
        iVar11 = (uint)*(byte *)(iVar11 + 0xe) * 0x5834 + param_1;
        *(undefined4 *)(iVar10 + 10) =
             *(undefined4 *)
              (
              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + iVar11 + 0x101);
        *(undefined2 *)(iVar10 + 0xe) =
             *(undefined2 *)
              (
              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + iVar11 + 0x105);
        iVar11 = *(int *)(param_3 + 0x24);
        *(undefined4 *)(iVar10 + 0x10) = *(undefined4 *)(iVar11 + 6);
        *(undefined2 *)(iVar10 + 0x14) = *(undefined2 *)(iVar11 + 10);
      }
      else {
        *(byte *)(iVar10 + 1) = *(byte *)(iVar10 + 1) & 0xfd | 1;
        if ((*(uint *)(param_3 + 0x18) & 0x80000) == 0) {
          iVar11 = (uint)*(ushort *)(param_3 + 0x1e) * 0x14c0 + param_1;
          *(undefined4 *)(iVar10 + 4) = *(undefined4 *)(iVar11 + 0xa1e0c);
          *(undefined2 *)(iVar10 + 8) = *(undefined2 *)(iVar11 + 0xa1e10);
        }
        else {
          *(byte *)(iVar10 + 1) = *(byte *)(iVar10 + 1) | 2;
        }
        if (((*(int *)(param_3 + 0x14) == 0) ||
            (iVar11 = *(int *)(*(int *)(param_3 + 0x14) + 0xafc), iVar11 == 0)) ||
           (*(char *)(iVar11 + 5) != '\x02')) {
          iVar11 = *(int *)(param_3 + 0x74);
          *(undefined4 *)(iVar10 + 10) = *(undefined4 *)(iVar11 + 0x1b);
          *(undefined2 *)(iVar10 + 0xe) = *(undefined2 *)(iVar11 + 0x1f);
        }
        else {
          *(undefined4 *)(iVar10 + 10) = *(undefined4 *)(iVar11 + 0x83);
          *(undefined2 *)(iVar10 + 0xe) = *(undefined2 *)(iVar11 + 0x87);
        }
        if ((*(uint *)(param_3 + 0x18) & 0x80000) != 0) {
          iVar11 = *(int *)(param_3 + 0x24);
          *(undefined4 *)(iVar10 + 0x18) = *(undefined4 *)(iVar11 + 6);
          *(undefined2 *)(iVar10 + 0x1c) = *(undefined2 *)(iVar11 + 10);
          *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + '\x06';
        }
        puVar12 = *(undefined4 **)(param_3 + 0x24);
        *(undefined4 *)(iVar10 + 0x10) = *puVar12;
        *(undefined2 *)(iVar10 + 0x14) = *(undefined2 *)(puVar12 + 1);
      }
    }
    else {
      *(byte *)(iVar10 + 1) = *(byte *)(iVar10 + 1) | 3;
      piVar5 = *(int **)(param_3 + 0x14);
      if (piVar5 == (int *)0x0) {
        if (-1 < DebugLevel) {
          printk("%s pTxBlk->pMacEntry == NULL!\n","ap_build_802_11_header");
        }
      }
      else {
        if (*piVar5 == 2) {
          iVar11 = (uint)*(ushort *)(param_3 + 0x1e) * 0x14c0 + param_1;
          *(undefined4 *)(iVar10 + 4) = *(undefined4 *)(iVar11 + 0xa1e0c);
          *(undefined2 *)(iVar10 + 8) = *(undefined2 *)(iVar11 + 0xa1e10);
          iVar11 = *(int *)(param_3 + 0x74);
          *(undefined4 *)(iVar10 + 10) = *(undefined4 *)(iVar11 + 0x1b);
          *(undefined2 *)(iVar10 + 0xe) = *(undefined2 *)(iVar11 + 0x1f);
        }
        else if (*piVar5 == 0x20001) {
          *(int *)(iVar10 + 4) = piVar5[0x3b];
          *(short *)(iVar10 + 8) = (short)piVar5[0x3c];
          iVar11 = *(int *)(param_3 + 0x10);
          *(undefined4 *)(iVar10 + 10) = *(undefined4 *)(iVar11 + 0x21);
          *(undefined2 *)(iVar10 + 0xe) = *(undefined2 *)(iVar11 + 0x25);
        }
        puVar12 = *(undefined4 **)(param_3 + 0x24);
        *(undefined4 *)(iVar10 + 0x10) = *puVar12;
        *(undefined2 *)(iVar10 + 0x14) = *(undefined2 *)(puVar12 + 1);
        iVar11 = *(int *)(param_3 + 0x24);
        *(undefined4 *)(iVar10 + 0x18) = *(undefined4 *)(iVar11 + 6);
        *(undefined2 *)(iVar10 + 0x1c) = *(undefined2 *)(iVar11 + 10);
        *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + '\x06';
        *(char *)(param_3 + 0x2c) = *(char *)(param_3 + 0x2c) + '\x06';
      }
    }
    if ((*(uint *)(param_3 + 100) & 1) == 0) {
      *(byte *)(iVar10 + 1) = *(byte *)(iVar10 + 1) | 0x40;
    }
    *(byte *)(param_3 + 0x83) = (byte)(((uint)*(byte *)(iVar9 + uVar14) << 0x1c) >> 0x1e);
    iVar10 = *(int *)(param_3 + 0x58) + uVar16;
    uVar16 = (uint)*(byte *)(param_3 + 0x35);
    *(byte *)(param_3 + 0x84) = *(byte *)(iVar9 + uVar14) >> 4;
  }
  else {
    iVar10 = iVar4 + 200 + uVar16;
    *(int *)(param_3 + 0x58) = iVar4 + 200;
    *(undefined1 *)(param_3 + 0x35) = 0x18;
    *(undefined1 *)(param_3 + 0x2c) = 0x18;
    iVar9 = *(int *)(param_3 + 8);
    piVar5 = *(int **)(param_3 + 0x14);
    *(byte *)(iVar10 + 1) =
         *(byte *)(iVar10 + 1) & 0xdf |
         (byte)(((uint)(*(int *)(param_3 + 0x18) << 0x19) >> 0x1f) << 5);
    iVar11 = iVar9 + (*(byte *)(param_3 + 0x1c) + 8) * 2;
    *(byte *)(iVar10 + 0x16) = *(byte *)(iVar10 + 0x16) & 0xf | *(char *)(iVar11 + 4) << 4;
    *(char *)(iVar10 + 0x17) = (char)(((uint)*(ushort *)(iVar11 + 4) << 0x14) >> 0x18);
    iVar9 = iVar9 + (uint)*(byte *)(param_3 + 0x1c) * 2;
    *(ushort *)(iVar9 + 0x14) = *(short *)(iVar9 + 0x14) + 1U & 0xfff;
    if ((*(uint *)(param_3 + 0x18) & 0x8000000) == 0) {
      puVar12 = *(undefined4 **)(param_3 + 0x24);
      if (*piVar5 == 2 || *piVar5 == 0x40001) {
        *(undefined4 *)(iVar10 + 0x10) = *puVar12;
        *(undefined2 *)(iVar10 + 0x14) = *(undefined2 *)(puVar12 + 1);
        if ((*(uint *)(param_3 + 0x18) & 0x80000) != 0) {
          iVar9 = *(int *)(param_3 + 0x24);
          *(undefined4 *)(iVar10 + 0x18) = *(undefined4 *)(iVar9 + 6);
          *(undefined2 *)(iVar10 + 0x1c) = *(undefined2 *)(iVar9 + 10);
          bVar13 = *(char *)(param_3 + 0x35) + 6;
          uVar16 = (uint)bVar13;
          *(byte *)(param_3 + 0x35) = bVar13;
          goto LAB_0001bf40;
        }
      }
      else {
        *(undefined4 *)(iVar10 + 0x10) = *(undefined4 *)((int)puVar12 + 6);
        *(undefined2 *)(iVar10 + 0x14) = *(undefined2 *)((int)puVar12 + 10);
      }
LAB_0001c1b4:
      uVar16 = (uint)*(byte *)(param_3 + 0x35);
    }
    else {
      *(byte *)(iVar10 + 1) = *(byte *)(iVar10 + 1) | 3;
      piVar5 = *(int **)(param_3 + 0x14);
      if (piVar5 == (int *)0x0) {
        if (DebugLevel < 0) goto LAB_0001c1b4;
        printk("%s pTxBlk->pMacEntry == NULL!\n","ap_build_cache_802_11_header");
        uVar16 = (uint)*(byte *)(param_3 + 0x35);
      }
      else {
        if (*piVar5 == 2) {
          iVar9 = (uint)*(ushort *)(param_3 + 0x1e) * 0x14c0 + param_1;
          *(undefined4 *)(iVar10 + 4) = *(undefined4 *)(iVar9 + 0xa1e0c);
          *(undefined2 *)(iVar10 + 8) = *(undefined2 *)(iVar9 + 0xa1e10);
          iVar9 = *(int *)(param_3 + 0x74);
          *(undefined4 *)(iVar10 + 10) = *(undefined4 *)(iVar9 + 0x1b);
          *(undefined2 *)(iVar10 + 0xe) = *(undefined2 *)(iVar9 + 0x1f);
        }
        else if (*piVar5 == 0x20001) {
          *(int *)(iVar10 + 4) = piVar5[0x3b];
          *(short *)(iVar10 + 8) = (short)piVar5[0x3c];
          iVar9 = *(int *)(param_3 + 0x10);
          *(undefined4 *)(iVar10 + 10) = *(undefined4 *)(iVar9 + 0x21);
          *(undefined2 *)(iVar10 + 0xe) = *(undefined2 *)(iVar9 + 0x25);
        }
        puVar12 = *(undefined4 **)(param_3 + 0x24);
        *(undefined4 *)(iVar10 + 0x10) = *puVar12;
        *(undefined2 *)(iVar10 + 0x14) = *(undefined2 *)(puVar12 + 1);
        iVar9 = *(int *)(param_3 + 0x24);
        *(undefined4 *)(iVar10 + 0x18) = *(undefined4 *)(iVar9 + 6);
        *(undefined2 *)(iVar10 + 0x1c) = *(undefined2 *)(iVar9 + 10);
        bVar13 = *(char *)(param_3 + 0x35) + 6;
        *(char *)(param_3 + 0x2c) = *(char *)(param_3 + 0x2c) + '\x06';
        uVar16 = (uint)bVar13;
        *(byte *)(param_3 + 0x35) = bVar13;
      }
    }
  }
LAB_0001bf40:
  pbVar3 = (byte *)(iVar10 + uVar16);
  if ((*(char *)(iVar4 + 0xc1) == '\0') ||
     ((uint)*(ushort *)(iVar4 + 0x14c) !=
      ((int)*(char *)(*(int *)(param_3 + 0xc) + 0x34) & 0xffffU |
      ((int)*(char *)(*(int *)(param_3 + 0xc) + 0x35) & 0xffffU) << 8))) {
    bVar13 = *(byte *)(param_3 + 0x1c) & 0xf;
    *pbVar3 = bVar13;
    if (((*(uint *)(*(int *)(param_3 + 0x14) + 0xb4) & 0x800) != 0) &&
       ((*(uint *)(param_3 + 0x18) & 0x800) != 0)) {
      *pbVar3 = bVar13 | 0x10;
    }
    pbVar3[1] = 0;
    bVar13 = *(char *)(param_3 + 0x35) + 2;
    *(char *)(param_3 + 0x2c) = *(char *)(param_3 + 0x2c) + '\x02';
    *(byte *)(param_3 + 0x35) = bVar13;
    if (bVar13 < 0x18) {
      printk(&_LC15,0x859);
      dump_stack();
    }
    iVar10 = *(int *)(param_3 + 0x28);
    __dest = (void *)((uint)(pbVar3 + 5) & 0xfffffffc);
    *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0xe;
    *(int *)(param_3 + 0x28) = iVar10 + -0xe;
    bVar17 = (*(byte *)(*(int *)(param_3 + 0xc) + 0x30) & 0x10) != 0;
    if (bVar17) {
      *(int *)(param_3 + 0x28) = iVar10 + -0x12;
    }
    cVar2 = (char)__dest - ((char)pbVar3 + '\x02');
    if (bVar17) {
      *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0x12;
    }
    *(char *)(param_3 + 0x34) = cVar2;
    *(char *)(iVar4 + 0x148) = cVar2;
    iVar10 = *(int *)(param_3 + 0x30);
    if ((uint)*(byte *)(iVar10 + -1) + (uint)*(byte *)(iVar10 + -2) * 0x100 < 0x5dd) {
      *(undefined4 *)(param_3 + 0x54) = 0;
    }
    else {
      __src = &SNAP_802_1H;
      *(undefined6 **)(param_3 + 0x54) = &SNAP_802_1H;
      iVar9 = memcmp(&IPX,(void *)(iVar10 + -2),2);
      if ((iVar9 == 0) || (iVar10 = memcmp(&APPLE_TALK,(void *)(iVar10 + -2),2), iVar10 == 0)) {
        __src = &SNAP_BRIDGE_TUNNEL;
        *(undefined6 **)(param_3 + 0x54) = &SNAP_BRIDGE_TUNNEL;
      }
      memmove(__dest,__src,6);
      pvVar6 = (void *)((int)__dest + 6);
      __dest = (void *)((int)__dest + 8);
      memmove(pvVar6,(void *)(*(int *)(param_3 + 0x30) + -2),2);
      *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + '\b';
    }
    *(short *)(iVar4 + 0x14c) =
         (short)*(char *)(*(int *)(param_3 + 0xc) + 0x34) |
         (short)*(char *)(*(int *)(param_3 + 0xc) + 0x35) << 8;
    *(undefined1 *)(iVar4 + 0x149) = *(undefined1 *)(param_3 + 0x35);
    *(undefined1 *)(iVar4 + 0x14a) = *(undefined1 *)(param_3 + 0x2c);
  }
  else {
    bVar13 = *(byte *)(param_3 + 0x1c) & 0xf;
    *pbVar3 = bVar13;
    if (((*(uint *)(*(int *)(param_3 + 0x14) + 0xb4) & 0x800) != 0) &&
       ((*(uint *)(param_3 + 0x18) & 0x800) != 0)) {
      *pbVar3 = bVar13 | 0x10;
    }
    __dest = (void *)(iVar10 + (uint)*(byte *)(iVar4 + 0x149));
    *(byte *)(param_3 + 0x35) = *(byte *)(iVar4 + 0x149);
    iVar10 = *(int *)(param_3 + 0x28);
    *(undefined1 *)(param_3 + 0x2c) = *(undefined1 *)(iVar4 + 0x14a);
    uVar1 = *(undefined1 *)(iVar4 + 0x148);
    *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0xe;
    *(int *)(param_3 + 0x28) = iVar10 + -0xe;
    *(undefined1 *)(param_3 + 0x34) = uVar1;
    if ((*(byte *)(*(int *)(param_3 + 0xc) + 0x30) & 0x10) != 0) {
      *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0x12;
      *(int *)(param_3 + 0x28) = iVar10 + -0x12;
    }
  }
LAB_0001bd7c:
  if (*(char *)(iVar4 + 0xc1) == '\0') {
    asic_write_tmac_info(param_1,*(undefined4 *)(param_3 + 0x58),param_3);
    if (((*(byte *)(*(int *)(param_3 + 0xc) + 0x30) & 0x4b) != 0) ||
       ((*(byte *)(*(int *)(param_3 + 0xc) + 0x4e) & 2) != 0)) {
      *(undefined1 *)(iVar4 + 0xc1) = 0;
    }
    __memzero((void *)(iVar4 + 0x150),0x40);
    if ((*(uint *)(param_3 + 0x18) & 0x800000) == 0) {
      pvVar6 = (void *)(*(int *)(param_3 + 0x58) + 4);
      memmove((void *)(iVar4 + 0x150),pvVar6,(int)__dest - (int)pvVar6);
    }
    __memzero((void *)(iVar4 + 200),0x80);
    memmove((void *)(iVar4 + 200),*(void **)(param_3 + 0x58),
            (int)__dest - (int)*(void **)(param_3 + 0x58));
  }
  else {
    asic_write_tmac_info(param_1,*(undefined4 *)(param_3 + 0x58),param_3);
  }
  FUN_0001bb8c(param_1,param_2,param_3);
  asic_write_tx_resource(param_1,param_3,1,local_2a);
  return 0;
}

