// module: mt7915.ko
// function: RTMPCheckHt @ 0x1389a8
// size: 1844 bytes
//

undefined4 RTMPCheckHt(int param_1,uint param_2,byte *param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  byte local_2a;
  byte local_29 [5];
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar3 = HcGetMaxStaNum(param_1);
  if (uVar3 <= param_2) {
    return 0;
  }
  iVar9 = param_2 * 0x14c0 + param_1;
  iVar4 = GetStaCfgByWdev(param_1,*(undefined4 *)(iVar9 + 0xa1d28));
  if (iVar4 == 0) {
    printk(&_LC16,0x3c2);
    dump_stack();
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s StaCfg NULL!! wcid %d entryType %d\n","RTMPCheckHt",param_2,
           *(undefined4 *)(iVar9 + 0xa1d20));
    puVar7 = *(undefined4 **)(iVar9 + 0xa1d28);
    if (puVar7 == (undefined4 *)0x0) {
      return 0;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("wdev %s, idx %d\n",*puVar7,*(undefined1 *)(puVar7 + 3));
    return 0;
  }
  iVar5 = wlan_config_get_amsdu_en(*(undefined4 *)(iVar9 + 0xa1d28));
  if (iVar5 != 0) {
    *(uint *)(iVar9 + 0xa1dd4) = *(uint *)(iVar9 + 0xa1dd4) | 8;
  }
  iVar5 = param_2 * 0x14c0 + param_1;
  iVar9 = wlan_config_get_ht_ldpc(*(undefined4 *)(iVar5 + 0xa1d28));
  if (((iVar9 != 0) && ((*(uint *)(iVar2 + 0x2c) & 0x40) != 0)) && ((*param_3 & 1) != 0)) {
    *(uint *)(iVar5 + 0xa1dd4) = *(uint *)(iVar5 + 0xa1dd4) | 0x1000000;
  }
  iVar5 = param_2 * 0x14c0 + param_1;
  iVar9 = wlan_config_get_ht_gi(*(undefined4 *)(iVar5 + 0xa1d28));
  uVar3 = (uint)*param_3;
  if (iVar9 == 1) {
    if ((*param_3 & 0x20) != 0) {
      *(uint *)(iVar5 + 0xa1dd4) = *(uint *)(iVar5 + 0xa1dd4) | 0x10;
      uVar3 = (uint)*param_3;
    }
    if ((uVar3 & 0x40) != 0) {
      iVar9 = param_2 * 0x14c0 + param_1;
      *(uint *)(iVar9 + 0xa1dd4) = *(uint *)(iVar9 + 0xa1dd4) | 0x20;
      uVar3 = (uint)*param_3;
    }
  }
  if (uVar3 >> 7 != 0) {
    iVar9 = param_2 * 0x14c0 + param_1;
    *(uint *)(iVar9 + 0xa1dd4) = *(uint *)(iVar9 + 0xa1dd4) | 0x40;
  }
  if ((param_3[1] & 3) != 0) {
    iVar9 = param_2 * 0x14c0 + param_1;
    *(uint *)(iVar9 + 0xa1dd4) = *(uint *)(iVar9 + 0xa1dd4) | 0x80;
  }
  if ((*(char *)(param_1 + 0x79507d) != '\0') && ((param_3[0x14] & 8) != 0)) {
    iVar9 = param_2 * 0x14c0 + param_1;
    *(uint *)(iVar9 + 0xa1dd4) = *(uint *)(iVar9 + 0xa1dd4) | 0x200;
  }
  iVar9 = param_2 * 0x14c0 + param_1;
  *(byte *)(iVar9 + 0xa2a24) = (byte)(((uint)param_3[2] << 0x1b) >> 0x1d);
  __memzero(iVar4 + 0x4193,0x10);
  uVar3 = wlan_config_get_ht_bw(*(undefined4 *)(iVar9 + 0xa1d28));
  if (uVar3 != 0) {
    *(undefined1 *)(iVar4 + 0x4197) = 1;
  }
  iVar9 = wlan_operate_get_rx_stream(*(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d28));
  if (iVar9 == 3) {
LAB_00138e28:
    *(undefined1 *)(iVar4 + 0x4195) = 0xff;
  }
  else {
    if (iVar9 == 4) {
      *(undefined1 *)(iVar4 + 0x4196) = 0xff;
      goto LAB_00138e28;
    }
    if (iVar9 != 2) goto LAB_00138bb0;
  }
  *(undefined1 *)(iVar4 + 0x4194) = 0xff;
LAB_00138bb0:
  *(undefined1 *)(iVar4 + 0x4193) = 0xff;
  uVar8 = ((uint)*(byte *)(param_4 + 1) << 0x1d) >> 0x1f & uVar3;
  *(byte *)(iVar4 + 0x4190) = *(byte *)(iVar4 + 0x4190) & 0xfd | (byte)(uVar8 << 1);
  if (uVar8 != 0) {
    iVar9 = RTMPCheckChannel(param_1,*(undefined1 *)(iVar4 + 0x4167),*(undefined1 *)(iVar4 + 0x4165)
                             ,*(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d28));
    if (iVar9 == 0) {
      *(byte *)(iVar4 + 0x4190) = *(byte *)(iVar4 + 0x4190) & 0xfd;
    }
    if ((*(byte *)(iVar4 + 0x4190) & 2) != 0) {
      iVar9 = param_2 * 0x14c0 + param_1;
      uVar8 = wlan_operate_get_ext_cha(*(undefined4 *)(iVar9 + 0xa1d28));
      if ((*(byte *)(param_4 + 1) & 3) != uVar8) {
        local_29[0] = (byte)(((uint)*(byte *)(iVar4 + 0x4190) << 0x1e) >> 0x1f);
        local_2a = 0;
        ht_ext_cha_adjust(param_1,*(undefined1 *)(iVar4 + 0x4165),local_29,&local_2a,
                          *(undefined4 *)(iVar9 + 0xa1d28));
        if (((*(byte *)(param_4 + 1) & 3) != local_2a) &&
           (bVar1 = *(byte *)(*(int *)(iVar9 + 0xa1d28) + 0x1a), 0xe < bVar1)) {
          if (-1 < DebugLevel) {
            uVar6 = wlan_operate_get_ext_cha();
            printk("RTMPCheckHt :  channel=%u,\tmy extcha=%u, root ap extcha=%u, inconsistent!!\n",
                   bVar1,uVar6,*(byte *)(param_4 + 1) & 3);
          }
          *(byte *)(iVar4 + 0x4190) = *(byte *)(iVar4 + 0x4190) & 0xfd;
          wlan_operate_set_ht_bw(*(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d28),0,0);
        }
      }
    }
    if (*(byte *)(iVar4 + 0x4165) < 0xf) {
      bVar1 = "rtmp_read_vow_parms_from_file"[param_1 + 7] & 1;
    }
    else {
      bVar1 = "rtmp_read_vow_parms_from_file"[param_1 + 7] & 2;
    }
    if (bVar1 != 0) {
      *(byte *)(iVar4 + 0x4190) = *(byte *)(iVar4 + 0x4190) & 0xfd;
    }
  }
  if (2 < DebugLevel) {
    printk("RTMPCheckHt:: HtCapInfo.ChannelWidth=%d, RecomWidth=%d, Configure HT_BW=%d, BW40MAvailForA/G=%d/%d\n"
           ,((uint)*(byte *)(iVar4 + 0x4190) << 0x1e) >> 0x1f,
           ((uint)*(byte *)(param_4 + 1) << 0x1d) >> 0x1f,uVar3,
           ((uint)(byte)"rtmp_read_vow_parms_from_file"[param_1 + 7] << 0x1e) >> 0x1f,
           (byte)"rtmp_read_vow_parms_from_file"[param_1 + 7] & 1);
  }
  iVar9 = DebugLevel;
  if (*(int *)(*(int *)(param_2 * 0x14c0 + param_1 + 0xa1d28) + 0x14) == 2) {
    *(byte *)(iVar4 + 0x4190) =
         *(byte *)(iVar4 + 0x4190) & 0xef | (byte)((((uint)*param_3 << 0x1b) >> 0x1f) << 4);
    if (2 < iVar9) {
      printk("RTMPCheckHt:: pHtCap->HtCapInfo.GF=%d\n",((uint)*param_3 << 0x1b) >> 0x1f);
    }
  }
  else {
    bVar1 = *param_3;
    uVar3 = wlan_config_get_greenfield();
    *(byte *)(iVar4 + 0x4190) =
         *(byte *)(iVar4 + 0x4190) & 0xef | (byte)((uVar3 & ((uint)bVar1 << 0x1b) >> 0x1f) << 4);
  }
  iVar9 = param_2 * 0x14c0 + param_1;
  *(byte *)(iVar4 + 0x4191) =
       *(byte *)(iVar4 + 0x4191) & 0xf7 | (byte)((((uint)param_3[1] << 0x1c) >> 0x1f) << 3);
  bVar1 = wlan_config_get_mmps(*(undefined4 *)(iVar9 + 0xa1d28));
  *(byte *)(iVar4 + 0x4190) = *(byte *)(iVar4 + 0x4190) & 0xf3 | (bVar1 & 3) << 2;
  uVar3 = wlan_config_get_ht_gi(*(undefined4 *)(iVar9 + 0xa1d28));
  *(byte *)(iVar4 + 0x4190) =
       *(byte *)(iVar4 + 0x4190) & 0xdf | (byte)((uVar3 & ((uint)*param_3 << 0x1a) >> 0x1f) << 5);
  uVar3 = wlan_config_get_ht_gi(*(undefined4 *)(iVar9 + 0xa1d28));
  *(byte *)(iVar4 + 0x4190) =
       *(byte *)(iVar4 + 0x4190) & 0xbf | (byte)((uVar3 & ((uint)*param_3 << 0x19) >> 0x1f) << 6);
  bVar1 = wlan_config_get_ht_stbc(*(undefined4 *)(iVar9 + 0xa1d28));
  *(byte *)(iVar4 + 0x4190) = *(byte *)(iVar4 + 0x4190) & 0x7f | (bVar1 & param_3[1] & 3) << 7;
  bVar1 = wlan_config_get_ht_stbc(*(undefined4 *)(iVar9 + 0xa1d28));
  *(byte *)(iVar4 + 0x4191) = *(byte *)(iVar4 + 0x4191) & 0xfc | bVar1 & *param_3 >> 7;
  if ((*(uint *)(iVar9 + 0xa1dd4) & 0x1000000) == 0) {
    *(byte *)(iVar4 + 0x4190) = *(byte *)(iVar4 + 0x4190) & 0xfe;
  }
  else {
    *(byte *)(iVar4 + 0x4190) = *(byte *)(iVar4 + 0x4190) | 1;
  }
  iVar9 = param_2 * 0x14c0 + param_1;
  *(byte *)(iVar4 + 0x4192) = *(byte *)(iVar4 + 0x4192) & 0xfc | param_3[2] & 3;
  *(byte *)(iVar4 + 0x4192) =
       *(byte *)(iVar4 + 0x4192) & 0xe3 | (byte)((((uint)param_3[2] << 0x1b) >> 0x1d) << 2);
  *(byte *)(iVar4 + 0x41a4) =
       *(byte *)(iVar4 + 0x41a4) & 0xfb | (byte)((((uint)param_3[0x14] << 0x1d) >> 0x1f) << 2);
  *(byte *)(iVar9 + 0xa29d8) =
       *(byte *)(iVar9 + 0xa29d8) & 0xfb | (byte)((((uint)param_3[0x14] << 0x1d) >> 0x1f) << 2);
  if (*(char *)(param_1 + 0x79507d) != '\0') {
    *(byte *)(iVar4 + 0x41a4) =
         *(byte *)(iVar4 + 0x41a4) & 0xf7 | (byte)((((uint)param_3[0x14] << 0x1c) >> 0x1f) << 3) | 4
    ;
  }
  if ((*(byte *)(iVar4 + 0x4190) & 2) == 0) {
    *(byte *)(iVar4 + 0x4197) = *(byte *)(iVar4 + 0x4190) & 2;
  }
  if (*(char *)(iVar2 + 0x96) != '\0') {
    mt_WrapSetETxBFCap(param_1,*(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d28),iVar4 + 0x41a5)
    ;
  }
  param_1 = param_2 * 0x14c0 + param_1;
  *(byte *)(param_1 + 0xa2a26) = (byte)(((uint)param_3[1] << 0x1c) >> 0x1f);
  *(byte *)(param_1 + 0xa2a30) = (byte)(((uint)*param_3 << 0x1c) >> 0x1e);
  *(byte *)(param_1 + 0xa2a25) = (byte)(((uint)param_3[2] << 0x1e) >> 0x1e);
  return 1;
}

