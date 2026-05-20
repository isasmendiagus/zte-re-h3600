// module: mt7915.ko
// function: header_packet_process @ 0xccb10
// size: 1760 bytes
//

undefined4 header_packet_process(int param_1,int param_2,int param_3,undefined4 param_4)

{
  ushort uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  byte *pbVar8;
  
  iVar3 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if ((iVar3 == 2) && (*(short *)(param_3 + 0x40) == 0 && param_2 != 0)) {
    RTMPFreeNdisPacket(param_1,param_2,*(short *)(param_3 + 0x40),1,param_4);
    if (2 < DebugLevel) {
      printk("%s():Packet Length is zero!\n","header_packet_process");
    }
    wlan_dbg_set_last_error(0,1,0x1b8c,"header_packet_process");
    return 2;
  }
  if ((((*(char *)(param_1 + 0x286285) == '\x01') && (*(char *)(param_1 + 0xa37233) != '\0')) &&
      (*(int *)(param_3 + 0x10) != 0)) &&
     (((*(byte *)(*(int *)(param_3 + 0x10) + 1) & 7) == 0 &&
      (uVar1 = *(ushort *)(param_3 + 0x4e),
      uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar1 < uVar4)))) {
    iVar3 = (uint)*(ushort *)(param_3 + 0x4e) * 0x14c0;
    if ((param_1 + iVar3 + 0xa1d20 != 0) &&
       ((*(int *)(param_1 + iVar3 + 0xa1d20) == 0x10 &&
        (pbVar8 = *(byte **)(param_3 + 0x1c),
        Air_Monitor_Pkt_Report_Action(param_1,(uint)*(ushort *)(param_3 + 0x4e),param_3),
        (*pbVar8 & 0xfc) != 0x40)))) {
      RTMPFreeNdisPacket(param_1,param_2);
      return 2;
    }
  }
  *(uint *)(param_1 + 0xa39e54) = (uint)*(ushort *)(param_3 + 0x40) + *(int *)(param_1 + 0xa39e54);
  uVar1 = *(ushort *)(param_3 + 0x40);
  *(int *)(param_1 + 0xa39e68) = *(int *)(param_1 + 0xa39e68) + 1;
  *(int *)(param_1 + 0xa39e3c) = *(int *)(param_1 + 0xa39e3c) + 1;
  *(uint *)(param_1 + 0xa39e40) = (uint)uVar1 + *(int *)(param_1 + 0xa39e40);
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    puVar6 = *(undefined4 **)(param_1 + 0xa77bb8);
LAB_000ccce4:
    net_ad_rx_done_handle(*puVar6,param_3);
    return 0;
  }
  if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
     (puVar6 = *(undefined4 **)(param_1 + 0xa77bb8), (puVar6[0x138] & 1) != 0)) goto LAB_000ccce4;
  uVar4 = *(uint *)(param_1 + 0xa39c48);
  *(uint *)(param_1 + 0xa39c48) = uVar4 + 1;
  *(uint *)(param_1 + 0xa39c4c) = *(int *)(param_1 + 0xa39c4c) + (uint)(0xfffffffe < uVar4);
  if (param_3 == 0) {
    printk("%s(): pRxBlk is NULL\n","rtmp_chk_rx_err");
    goto LAB_000ccc94;
  }
  pbVar8 = *(byte **)(param_3 + 0x10);
  if (pbVar8 == (byte *)0x0) {
    printk("%s(): pRxBlk->pRxInfo is NULL\n","rtmp_chk_rx_err");
    goto LAB_000ccc94;
  }
  iVar7 = *(int *)(param_3 + 0x1c);
  iVar3 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar3 == 2) {
    uVar4 = *(uint *)(param_3 + 0x44);
    if ((uVar4 & 0x400000) != 0) {
      *(int *)(param_1 + 0x9dcd0) = *(int *)(param_1 + 0x9dcd0) + 1;
      goto LAB_000ccc94;
    }
    if ((uVar4 & 0x200000) != 0) {
      if (0 < DebugLevel) {
        printk("CM Length Error\n, WlanIndex = %d\n",*(undefined2 *)(param_3 + 0x4e));
      }
      goto LAB_000ccc94;
    }
    if (*(char *)(param_3 + 0x74) != '\0') {
      if (0 < DebugLevel) {
        printk("Deammsdu Fail\n, WlanIndex = %d\n",*(undefined2 *)(param_3 + 0x4e));
      }
      goto LAB_000ccc94;
    }
    if ((uVar4 & 0x800000) != 0) {
      if (2 < DebugLevel) {
        printk("TkipMicErr Fail\n");
      }
      goto LAB_000ccc94;
    }
    if (*(char *)(param_1 + 0x286285) == '\0') {
      **(byte **)(param_3 + 0x10) = **(byte **)(param_3 + 0x10) | 0x80;
    }
    uVar4 = (uint)pbVar8[1];
    if (((pbVar8[1] & 0x10) != 0) && (*(char *)(param_3 + 0x72) != '\0')) {
      uVar1 = *(ushort *)(param_3 + 0x4e);
      uVar4 = HcGetMaxStaNum(param_1);
      if (((uVar1 < uVar4) &&
          (((iVar3 = (uint)*(ushort *)(param_3 + 0x4e) * 0x14c0, param_1 + iVar3 + 0xa1d20 != 0 &&
            (iVar3 = param_1 + iVar3,
            *(int *)(iVar3 + 0xa1d20) == 2 ||
            (*(int *)(iVar3 + 0xa1d20) - 0x20001U & 0xfffdffff) == 0)) &&
           (*(int *)(iVar3 + 0xa3158) == 0)))) &&
         (((*(char *)(iVar3 + 0xa315c) == '\0' && ((*(uint *)(param_3 + 0x44) & 0x400000) == 0)) &&
          ((*(uint *)(param_3 + 0x44) & 0xb00000) == 0)))) {
        *(undefined4 *)(iVar3 + 0xa3150) = 0;
        *(undefined1 *)(iVar3 + 0xa315c) = 1;
      }
      goto LAB_000ccbf4;
    }
  }
  else {
LAB_000ccbf4:
    uVar4 = (uint)pbVar8[1];
  }
  if ((uVar4 & 1) != 0) {
    if (*(char *)(param_1 + 0x286285) == '\0') {
      iVar3 = (uint)*(byte *)(param_3 + 0x58) -
              (int)"rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x12];
      if (iVar3 < -0x56) {
        *(short *)(&DAT_00580d10 + param_1) = *(short *)(&DAT_00580d10 + param_1) + 1;
      }
      else {
        if (iVar3 < -0x51) {
          iVar3 = 0xd12;
        }
        else if (iVar3 < -0x4c) {
          iVar3 = 0xd14;
        }
        else if (iVar3 < -0x47) {
          iVar3 = 0xd16;
        }
        else if (iVar3 < -0x42) {
          iVar3 = 0xd18;
        }
        else if (iVar3 < -0x3d) {
          iVar3 = 0xd1a;
        }
        else if (iVar3 < -0x38) {
          iVar3 = 0xd1c;
        }
        else {
          iVar3 = 0xd1e;
        }
        *(short *)(param_1 + 0x580000 + iVar3) = *(short *)(param_1 + 0x580000 + iVar3) + 1;
      }
    }
    goto LAB_000ccc94;
  }
  cVar2 = *(char *)(param_1 + 0x286285);
  if (cVar2 == '\0') {
    if ((*(ushort *)(param_3 + 0x40) < 0xe) || (0xf00 < *(ushort *)(param_3 + 0x48))) {
      if (-1 < DebugLevel) {
        printk("rx pkt len err(%d, %d)\n",*(ushort *)(param_3 + 0x40),
               *(undefined2 *)(param_3 + 0x48));
      }
      goto LAB_000ccc94;
    }
    if ((*(int *)(param_3 + 0x1c) != 0) && ((*(byte *)(iVar7 + 1) & 1) != 0)) {
      if (-1 < DebugLevel) {
        printk("%s: Line(%d) (ToDs Packet not allow in STA Mode)\n","rtmp_chk_rx_err",0x15f7);
      }
      goto LAB_000ccc94;
    }
  }
  if (((pbVar8[2] & 1) != 0) && (uVar5 = uVar4 & 6, uVar5 != 0)) {
    if (uVar5 == 4) {
      if (2 < DebugLevel) {
        printk("RxErr: ICV ok but MICErr");
        cVar2 = *(char *)(param_1 + 0x286285);
      }
    }
    else if (uVar5 == 2) {
      if (2 < DebugLevel) {
        printk("RxErr: ICV Err");
        cVar2 = *(char *)(param_1 + 0x286285);
      }
    }
    else if (uVar5 == 6) {
      if (2 < DebugLevel) {
        printk("RxErr: Key not valid");
        cVar2 = *(char *)(param_1 + 0x286285);
      }
    }
    else if (2 < DebugLevel) {
      printk("RxErr: CipherErr 0x%x",(uVar4 << 0x1d) >> 0x1e);
      cVar2 = *(char *)(param_1 + 0x286285);
    }
    uVar4 = *(uint *)(param_1 + 0xa39c68);
    *(uint *)(param_1 + 0xa39c68) = uVar4 + 1;
    *(uint *)(param_1 + 0xa39c6c) = *(int *)(param_1 + 0xa39c6c) + (uint)(0xfffffffe < uVar4);
    if ((cVar2 == '\x01') && ((*pbVar8 & 0x10) != 0)) {
      if (*(short *)(param_3 + 0x4e) == 0xff) {
        return 0;
      }
      if (((*(byte *)(iVar7 + 1) & 2) == 0) &&
         ((uint)*(byte *)(param_3 + 0x52) <
          (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [param_1 + 0xda])) {
        iVar3 = (uint)*(byte *)(param_3 + 0x52) * 0x5834 + param_1;
        *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + iVar3 + 0x30) =
             *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + iVar3 + 0x30) + 1;
        *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + iVar3 + 0x2c) =
             *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + iVar3 + 0x2c) + 1;
      }
    }
    if (*(int *)(param_3 + 0x1c) != 0) {
LAB_000ccc94:
      *(int *)(param_1 + 0xa39bf0) = *(int *)(param_1 + 0xa39bf0) + 1;
      wlan_dbg_set_last_error(0,1,0x1c13,"header_packet_process");
      RTMPFreeNdisPacket(param_1,param_2);
      if (DebugLevel < 3) {
        return 2;
      }
      printk("%s(): CheckRxError!\n","header_packet_process");
      return 2;
    }
  }
  return 0;
}

