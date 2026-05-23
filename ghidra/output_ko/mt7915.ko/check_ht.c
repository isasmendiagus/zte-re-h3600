// module: mt7915.ko
// function: check_ht @ 0x1390e0
// size: 1048 bytes
//

undefined4 check_ht(int param_1,uint param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  int iVar8;
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar4 = HcGetMaxStaNum(param_1);
  if (uVar4 <= param_2) {
    return 0;
  }
  iVar8 = param_2 * 0x14c0 + param_1;
  iVar5 = GetStaCfgByWdev(param_1,*(undefined4 *)(iVar8 + 0xa1d28));
  if (iVar5 == 0) {
    printk(&_LC22,0x47a);
    dump_stack();
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s StaCfg NULL!! wcid %d entryType %d\n","check_ht",param_2,
           *(undefined4 *)(iVar8 + 0xa1d20));
    puVar6 = *(undefined4 **)(iVar8 + 0xa1d28);
    if (puVar6 == (undefined4 *)0x0) {
      return 0;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("wdev %s, idx %d\n",*puVar6,*(undefined1 *)(puVar6 + 3));
    return 0;
  }
  __memzero(iVar5 + 0x4193,0x10);
  *(undefined1 *)(iVar5 + 0x4197) = 1;
  iVar8 = wlan_operate_get_rx_stream(*(undefined4 *)(iVar8 + 0xa1d28));
  if (iVar8 == 3) {
LAB_001393a4:
    *(undefined1 *)(iVar5 + 0x4195) = 0xff;
  }
  else {
    if (iVar8 == 4) {
      *(undefined1 *)(iVar5 + 0x4196) = 0xff;
      goto LAB_001393a4;
    }
    if (iVar8 != 2) goto LAB_00139190;
  }
  *(undefined1 *)(iVar5 + 0x4194) = 0xff;
LAB_00139190:
  iVar8 = param_2 * 0x14c0 + param_1;
  *(undefined1 *)(iVar5 + 0x4193) = 0xff;
  uVar4 = wlan_config_get_ht_bw(*(undefined4 *)(iVar8 + 0xa1d28));
  uVar7 = ((uint)*(byte *)(param_3 + 0x4f) << 0x1d) >> 0x1f & uVar4;
  *(byte *)(iVar5 + 0x4190) = *(byte *)(iVar5 + 0x4190) & 0xfd | (byte)(uVar7 << 1);
  if (uVar7 != 0) {
    iVar8 = RTMPCheckChannel(param_1,*(undefined1 *)(iVar5 + 0x4167),*(undefined1 *)(iVar5 + 0x4165)
                             ,*(undefined4 *)(iVar8 + 0xa1d28));
    if (iVar8 == 0) {
      *(byte *)(iVar5 + 0x4190) = *(byte *)(iVar5 + 0x4190) & 0xfd;
    }
    if (*(byte *)(iVar5 + 0x4165) < 0xf) {
      bVar2 = "rtmp_read_vow_parms_from_file"[param_1 + 7] & 1;
    }
    else {
      bVar2 = "rtmp_read_vow_parms_from_file"[param_1 + 7] & 2;
    }
    if (bVar2 != 0) {
      *(byte *)(iVar5 + 0x4190) = *(byte *)(iVar5 + 0x4190) & 0xfd;
    }
  }
  if (2 < DebugLevel) {
    printk("%s(): HtCapInfo.ChannelWidth=%d, RecomWidth=%d, Configure HT_BW=%d, BW40MAvailForA/G=%d/%d\n"
           ,"check_ht",((uint)*(byte *)(iVar5 + 0x4190) << 0x1e) >> 0x1f,
           ((uint)*(byte *)(param_3 + 0x4f) << 0x1d) >> 0x1f,uVar4,
           ((uint)(byte)"rtmp_read_vow_parms_from_file"[param_1 + 7] << 0x1e) >> 0x1f,
           (byte)"rtmp_read_vow_parms_from_file"[param_1 + 7] & 1);
  }
  iVar8 = param_2 * 0x14c0 + param_1;
  bVar2 = *(byte *)(param_3 + 0x34);
  uVar4 = wlan_config_get_greenfield(*(undefined4 *)(iVar8 + 0xa1d28));
  *(byte *)(iVar5 + 0x4190) =
       *(byte *)(iVar5 + 0x4190) & 0xef | (byte)((uVar4 & ((uint)bVar2 << 0x1b) >> 0x1f) << 4);
  *(byte *)(iVar5 + 0x4191) =
       *(byte *)(iVar5 + 0x4191) & 0xf7 |
       (byte)((((uint)*(byte *)(param_3 + 0x35) << 0x1c) >> 0x1f) << 3);
  bVar2 = wlan_config_get_mmps(*(undefined4 *)(iVar8 + 0xa1d28));
  *(byte *)(iVar5 + 0x4190) = *(byte *)(iVar5 + 0x4190) & 0xf3 | (bVar2 & 3) << 2;
  uVar4 = wlan_config_get_ht_gi(*(undefined4 *)(iVar8 + 0xa1d28));
  *(byte *)(iVar5 + 0x4190) =
       *(byte *)(iVar5 + 0x4190) & 0xdf |
       (byte)((uVar4 & ((uint)*(byte *)(param_3 + 0x34) << 0x1a) >> 0x1f) << 5);
  uVar4 = wlan_config_get_ht_gi(*(undefined4 *)(iVar8 + 0xa1d28));
  *(byte *)(iVar5 + 0x4190) =
       *(byte *)(iVar5 + 0x4190) & 0xbf |
       (byte)((uVar4 & ((uint)*(byte *)(param_3 + 0x34) << 0x19) >> 0x1f) << 6);
  bVar2 = wlan_config_get_ht_stbc(*(undefined4 *)(iVar8 + 0xa1d28));
  *(byte *)(iVar5 + 0x4190) =
       *(byte *)(iVar5 + 0x4190) & 0x7f | (bVar2 & *(byte *)(param_3 + 0x35) & 3) << 7;
  bVar2 = wlan_config_get_ht_stbc(*(undefined4 *)(iVar8 + 0xa1d28));
  *(byte *)(iVar5 + 0x4191) =
       *(byte *)(iVar5 + 0x4191) & 0xfc | bVar2 & *(byte *)(param_3 + 0x34) >> 7;
  if ((*(uint *)(iVar3 + 0x2c) & 0x40) == 0) {
    *(byte *)(iVar5 + 0x4190) = *(byte *)(iVar5 + 0x4190) & 0xfe;
  }
  else {
    bVar2 = wlan_config_get_ht_ldpc(*(undefined4 *)(iVar8 + 0xa1d28));
    *(byte *)(iVar5 + 0x4190) =
         *(byte *)(iVar5 + 0x4190) & 0xfe |
         bVar2 & (byte)(((uint)*(byte *)(param_3 + 0x34) << 0x1f) >> 0x1f);
  }
  bVar2 = *(byte *)(iVar5 + 0x41a4);
  *(byte *)(iVar5 + 0x4192) = *(byte *)(iVar5 + 0x4192) & 0xfc | *(byte *)(param_3 + 0x36) & 3;
  *(byte *)(iVar5 + 0x4192) =
       *(byte *)(iVar5 + 0x4192) & 0xe3 |
       (byte)((((uint)*(byte *)(param_3 + 0x36) << 0x1b) >> 0x1d) << 2);
  bVar1 = (byte)((((uint)*(byte *)(param_3 + 0x48) << 0x1d) >> 0x1f) << 2);
  *(byte *)(iVar5 + 0x41a4) = bVar2 & 0xfb | bVar1;
  if (*(char *)(param_1 + 0x79507d) != '\0') {
    *(byte *)(iVar5 + 0x41a4) =
         bVar2 & 0xf3 | bVar1 | (byte)((((uint)*(byte *)(param_3 + 0x48) << 0x1c) >> 0x1f) << 3) | 4
    ;
  }
  if ((*(byte *)(iVar5 + 0x4190) & 2) == 0) {
    *(byte *)(iVar5 + 0x4197) = *(byte *)(iVar5 + 0x4190) & 2;
  }
  if (*(char *)(iVar3 + 0x96) != '\0') {
    mt_WrapSetETxBFCap(param_1,*(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d28),iVar5 + 0x41a5)
    ;
    return 1;
  }
  return 1;
}

