// module: mt7915.ko
// function: ap_ieee_802_11_data_rx @ 0x1db60
// size: 1572 bytes
//

undefined4 ap_ieee_802_11_data_rx(int param_1,int param_2,int param_3,uint *param_4)

{
  char cVar1;
  int iVar2;
  ushort uVar3;
  byte bVar4;
  short sVar5;
  int iVar6;
  code *pcVar7;
  char *pcVar9;
  byte *pbVar10;
  byte *pbVar11;
  undefined4 uVar12;
  ushort *__s2;
  uint uVar8;
  
  iVar6 = *(int *)(param_2 + 0x904);
  pbVar10 = *(byte **)(param_3 + 0x10);
  pbVar11 = *(byte **)(param_3 + 0x1c);
  if (3 < DebugLevel) {
    uVar8 = *(uint *)(param_3 + 0x44);
    printk("%s(): wcid=%d, wdev_idx=%d, pRxBlk->Flags=0x%x, fRX_AP/STA/ADHOC=0x%x/0x%x/0x%x, Type/SubType=%d/%d, FrmDS/ToDS=%d/%d\n"
           ,"ap_ieee_802_11_data_rx",(short)param_4[0x38],*(undefined1 *)(param_2 + 0xc),uVar8,
           uVar8 & 0x100,uVar8 & 0x200,uVar8 & 0x400,((uint)*pbVar11 << 0x1c) >> 0x1e,*pbVar11 >> 4,
           ((uint)pbVar11[1] << 0x1e) >> 0x1f,pbVar11[1] & 1);
  }
  pcVar7 = *(code **)(iVar6 + 0x68);
  if (pcVar7 != (code *)0x0) {
    (*pcVar7)(param_1,param_2,param_3);
  }
  param_4[0x2ba] = 0;
  *(undefined4 *)(param_1 + (uint)(ushort)param_4[0x38] * 0x620 + 0x2f954) = 0;
  if ((*(uint *)(param_3 + 0x44) & 0x800) == 0) {
    iVar2 = 0x18;
  }
  else {
    iVar2 = 0x1e;
  }
  *(short *)(param_3 + 0x40) = *(short *)(param_3 + 0x40) - (short)iVar2;
  pcVar9 = (char *)(*(int *)(param_3 + 0x1c) + iVar2);
  uVar8 = ((uint)*pbVar11 << 0x18) >> 0x1c & 8;
  bVar4 = (byte)uVar8;
  if (uVar8 != 0) {
    bVar4 = *(byte *)(*(int *)(param_3 + 0x1c) + iVar2) & 0xf;
    if ((*(short *)(param_1 + ((uint)*(ushort *)(param_3 + 0x4e) * 0xa60 +
                               (uint)*(byte *)(param_3 + 0x53) + 0x514f8) * 2 + 4) == 0) ||
       ((*pbVar10 & 0x10) == 0)) {
      *pbVar10 = *pbVar10 & 0xfe;
      cVar1 = *pcVar9;
    }
    else {
      *pbVar10 = *pbVar10 | 1;
      cVar1 = *pcVar9;
    }
    if (cVar1 < '\0') {
      *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 2;
      *(int *)(param_1 + 0xa39ee0) = *(int *)(param_1 + 0xa39ee0) + 1;
    }
    if ((*pbVar10 & 1) != 0) {
      *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 1;
      *(int *)(param_1 + 0xa39f00) = *(int *)(param_1 + 0xa39f00) + 1;
    }
    pcVar9 = pcVar9 + 2;
    *(short *)(param_3 + 0x40) = *(short *)(param_3 + 0x40) + -2;
  }
  *(byte *)(param_3 + 0x4a) = bVar4;
  iVar2 = rx_chk_duplicate_frame(param_1,param_3,param_2);
  if (iVar2 == 1) {
    if (2 < DebugLevel) {
      printk("%s(): duplicate frame drop it!\n","ap_ieee_802_11_data_rx");
    }
    wlan_dbg_set_last_error(0,1,0x109a,"ap_ieee_802_11_data_rx");
    return 0;
  }
  iVar2 = rx_chk_amsdu_invalid_frame(param_1,param_3,param_2);
  if (iVar2 == 1) {
    if (2 < DebugLevel) {
      printk("%s(): invalid amsdu frame drop it!\n","ap_ieee_802_11_data_rx");
    }
    wlan_dbg_set_last_error(0,1,0x10a3,"ap_ieee_802_11_data_rx");
    return 0;
  }
  if ((pbVar11[1] & 0x80) != 0) {
    if ((*(byte *)(param_3 + 99) < 0x40) && ((param_4[0x2d] & 2) != 0)) {
      *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 4;
    }
    else {
      pcVar9 = pcVar9 + 4;
      *(short *)(param_3 + 0x40) = *(short *)(param_3 + 0x40) + -4;
    }
  }
  if ((*pbVar11 & 0x40) != 0) {
    if (3 < DebugLevel) {
      printk("%s(): Null/QosNull frame!\n","ap_ieee_802_11_data_rx");
    }
    wlan_dbg_radio_statistics_inc(0,0xd);
    return 0;
  }
  if ((pbVar10[1] & 0x40) != 0) {
    pcVar9 = pcVar9 + 2;
    *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 0x10;
  }
  if (*(char *)(param_3 + 0x73) != '\0') {
    sVar5 = *(short *)(param_3 + 0x40);
    if ((*(byte *)(*(int *)(param_3 + 0x18) + 6) & 0x40) != 0) {
      pcVar9 = pcVar9 + 2;
      sVar5 = sVar5 + -2;
    }
    pcVar9 = pcVar9 + 0xe;
    *(short *)(param_3 + 0x40) = sVar5 + -0xe;
  }
  *(char **)(param_3 + 0x3c) = pcVar9;
  param_4[0x2ba] = 0;
  *(undefined4 *)(param_1 + (uint)(ushort)param_4[0x38] * 0x620 + 0x2f954) = 0;
  if ((*pbVar10 & 0x10) != 0) {
    *(int *)(&DAT_0036b820 + param_1) = *(int *)(&DAT_0036b820 + param_1) + 1;
    param_4[0x4e] = (uint)*(ushort *)(param_3 + 0x62);
    if ((*(byte *)(param_3 + 99) & 2) == 0) {
      param_4[0x31d] = param_4[0x31d] + 1;
    }
    else {
      param_4[0x31e] = param_4[0x31e] + 1;
    }
  }
  *(undefined1 *)(param_2 + 0x908) = *(undefined1 *)(param_3 + 0x5c);
  *(undefined1 *)(param_2 + 0x909) = *(undefined1 *)(param_3 + 0x5d);
  *(short *)(param_4 + 0x5d) = (short)*(char *)(param_3 + 0x60);
  *(undefined2 *)((int)param_4 + 0x176) = 1;
  if ((*(char *)(param_3 + 0x22) == '\0') && ((pbVar11[1] & 4) == 0)) {
    if (*(int *)(param_3 + 0x38) == 0) goto LAB_0001df34;
  }
  else {
    de_fragment_data_pkt(param_1,param_3);
    if (*(int *)(param_3 + 0x38) == 0) goto LAB_0001df34;
    if (((pbVar11[1] & 0x40) != 0) && ((param_4[0xb1] & 0x10) != 0)) {
      *(short *)(param_3 + 0x40) = *(short *)(param_3 + 0x40) + -8;
      iVar2 = rtmp_chk_tkip_mic(param_1,param_4,param_3);
      if (iVar2 == 0) {
        return 1;
      }
    }
  }
  uVar3 = *(ushort *)(param_3 + 0x48);
  uVar8 = param_4[0x4c6];
  param_4[0x4c6] = uVar8 + uVar3;
  param_4[0x4c7] = param_4[0x4c7] + (uint)CARRY4(uVar8,(uint)uVar3);
  *(uint *)(param_1 + 0xa78a1c) = (uint)*(ushort *)(param_3 + 0x48) + *(int *)(param_1 + 0xa78a1c);
  uVar8 = param_4[0x4c2];
  param_4[0x4c2] = uVar8 + 1;
  param_4[0x4c3] = param_4[0x4c3] + (uint)(0xfffffffe < uVar8);
  param_4[0x4e2] = param_4[0x4e2] + 1;
  uVar8 = *param_4;
  if (uVar8 == 2) {
    *(undefined2 *)(*(int *)(param_3 + 0x38) + 0x42) = *(undefined2 *)(param_3 + 0x4e);
    uVar8 = *param_4;
  }
  if (((uVar8 == 0x20001) || ((uVar8 & 4) != 0)) && (*(char *)(param_2 + 0x890) != '\0')) {
    pbVar10 = *(byte **)(param_3 + 0x30);
    if (*pbVar10 == 0xff) {
      bVar4 = 0;
    }
    else {
      bVar4 = *pbVar10 & 1;
    }
    if (bVar4 != 0) {
      __s2 = *(ushort **)(param_3 + 0x3c);
      uVar12 = *(undefined4 *)(param_3 + 0x2c);
      iVar2 = memcmp(&SNAP_802_1H,__s2,6);
      if (iVar2 == 0) {
        uVar3 = __s2[3];
        __s2 = __s2 + 3;
      }
      else {
        uVar3 = *__s2;
      }
      uVar3 = uVar3 << 8 | uVar3 >> 8;
      if (uVar3 == 0x800) {
        IGMPSnooping(param_1,pbVar10,uVar12,__s2,param_4,*(undefined2 *)(param_3 + 0x4e));
      }
      else if (uVar3 == 0x86dd) {
        MLDSnooping(param_1,pbVar10,uVar12,__s2,param_4,*(undefined2 *)(param_3 + 0x4e));
      }
    }
  }
  if ((*(uint *)(param_3 + 0x44) & 0x40000) == 0) {
    rx_data_frm_announce(param_1,param_4,param_3,param_2);
  }
  else {
    rx_802_3_data_frm_announce();
  }
LAB_0001df34:
  (**(code **)(iVar6 + 0x84))(param_1,param_2,*(undefined1 *)(param_3 + 0x4a),0);
  return 1;
}

