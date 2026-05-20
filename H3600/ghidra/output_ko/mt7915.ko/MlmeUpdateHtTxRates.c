// module: mt7915.ko
// function: MlmeUpdateHtTxRates @ 0x12c1ac
// size: 1704 bytes
//

void MlmeUpdateHtTxRates(int param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  byte bVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  char cVar8;
  uint uVar9;
  byte bVar10;
  bool bVar11;
  byte *local_30;
  int local_2c;
  
  bVar10 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
  if (3 < DebugLevel) {
    printk("%s()===>\n","MlmeUpdateHtTxRates");
  }
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s(): invalid wdev (%p)\n","MlmeUpdateHtTxRates",0);
    return;
  }
  iVar6 = GetStaCfgByWdev(param_1,param_2);
  wlan_operate_get_addht(param_2);
  if (*(int *)(param_2 + 0x14) == 2 || *(int *)(param_2 + 0x14) == 0x100) {
    local_2c = wlan_operate_get_ht_bw(param_2);
  }
  else {
    local_2c = wlan_config_get_ht_bw();
  }
  local_30 = (byte *)wlan_operate_get_ht_cap(param_2);
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    iVar7 = HcGetBandByWdev(param_2);
    if (iVar7 == 0) {
      bVar10 = "SetPartProfileParameters"[param_1 + 0x1a];
    }
    else {
      bVar10 = "rtmp_read_vow_parms_from_file"[param_1];
    }
  }
  if ((iVar6 == 0) ||
     ((((*(uint *)(param_1 + 0x795124) & 2) == 0 && ((*(uint *)(iVar6 + 0x212464) & 1) == 0)) ||
      ((*(int *)(param_2 + 0x14) - 2U & 0xfffffffd) != 0)))) {
    if (*(char *)(param_2 + 0x891) == '\0') {
      return;
    }
    local_30 = (byte *)wlan_operate_get_ht_cap(param_2);
    uVar9 = ((uint)*local_30 << 0x1b) >> 0x1f;
    bVar4 = *local_30 >> 7;
    if (bVar10 < 2) {
      bVar4 = 0;
    }
    if (bVar4 == 0) {
      bVar10 = *(byte *)(param_2 + 0x8b5) & 0xfb;
    }
    else {
      bVar10 = *(byte *)(param_2 + 0x8b5) | 4;
    }
    *(byte *)(param_2 + 0x8b5) = bVar10;
    iVar7 = param_2 + 0x891;
  }
  else {
    if (*(char *)(iVar6 + 0x40e0) == '\0') {
      return;
    }
    uVar9 = ((uint)*(byte *)(iVar6 + 0x40fc) << 0x1d) >> 0x1f;
    iVar7 = iVar6 + 0x40e0;
    if (((*local_30 & 0x80) == 0) || (*(byte *)(iVar6 + 0x40fc) >> 6 == 0 || bVar10 < 2)) {
      *(byte *)(param_2 + 0x8b5) = *(byte *)(param_2 + 0x8b5) & 0xfb;
    }
    else {
      *(byte *)(param_2 + 0x8b5) = *(byte *)(param_2 + 0x8b5) | 4;
    }
  }
  if (uVar9 == 0) {
    cVar8 = '\x02';
  }
  else {
    cVar8 = '\x03';
  }
  *(byte *)(param_2 + 0x8b5) = *(byte *)(param_2 + 0x8b5) & 0x1f | cVar8 << 5;
  if (local_2c != 0) {
    uVar3 = *(ushort *)(param_2 + 0x8b4);
  }
  else {
    uVar3 = *(ushort *)(param_2 + 0x8b4);
  }
  *(ushort *)(param_2 + 0x8b4) = uVar3 & 0xfe7f | (ushort)(local_2c != 0) << 7;
  if ((*(ushort *)(param_2 + 0x8b4) & 0x180) == 0) {
    uVar9 = (uint)*local_30 << 0x1a;
  }
  else {
    uVar9 = (uint)*local_30 << 0x19;
  }
  *(byte *)(param_2 + 0x8b5) = *(byte *)(param_2 + 0x8b5) & 0xfd | (byte)((uVar9 >> 0x1f) << 1);
  if (*(char *)(param_2 + 0x897) != '\0') {
    *(byte *)(param_2 + 0x8b4) = *(byte *)(param_2 + 0x8b4) & 0xc0 | 0x20;
  }
  bVar4 = get_ht_max_mcs(param_2 + 0x893,iVar7 + 2);
  uVar9 = *(ushort *)(param_2 + 0x8b6) & 0xfffffe7f;
  cVar8 = *(char *)(param_2 + 0x893);
  *(byte *)(param_2 + 0x8b6) = (byte)uVar9 & 0xc0;
  *(byte *)(param_2 + 0x8b7) = (byte)(uVar9 >> 8) & 0xf9;
  bVar4 = bVar4 & 0x3f;
  bVar10 = *(byte *)(param_2 + 0x8b4) & 0xc0;
  *(byte *)(param_2 + 0x8b4) = bVar10 | bVar4;
  iVar6 = DebugLevel;
  if (*(char *)(param_1 + 0x286285) == '\0') {
    if (cVar8 != -1) {
      if (*(char *)(param_2 + 0x897) != '\0') {
        *(byte *)(param_2 + 0x8b4) = bVar10 | 0x20;
        *(byte *)(param_2 + 0x8b6) = *(byte *)(param_2 + 0x8b6) & 0xc0 | 0x20;
        if (2 < iVar6) {
          printk("%s():<=== Use Fixed MCS = %d\n","MlmeUpdateHtTxRates");
          cVar8 = *(char *)(param_2 + 0x893);
        }
      }
      iVar6 = 0x1f;
      do {
        cVar1 = (char)(byte)iVar6 >> 3;
        uVar9 = 1 << ((short)cVar1 * -8 + iVar6 & 0xffU) & 0xff;
        if (((uVar9 & *(byte *)(param_2 + cVar1 + 0x893)) != 0) &&
           ((uVar9 & *(byte *)(iVar7 + cVar1 + 2)) != 0)) {
          bVar4 = (byte)iVar6 & 0x3f;
          *(byte *)(param_2 + 0x8b4) = *(byte *)(param_2 + 0x8b4) & 0xc0 | bVar4;
          *(byte *)(param_2 + 0x8b6) = *(byte *)(param_2 + 0x8b6) & 0xc0 | bVar4;
          goto LAB_0012c43c;
        }
        bVar11 = iVar6 != 0;
        iVar6 = iVar6 + -1;
      } while (bVar11);
      bVar4 = *(byte *)(param_2 + 0x8b4) & 0x3f;
      goto LAB_0012c43c;
    }
    *(byte *)(param_2 + 0x8b3) =
         *(byte *)(param_2 + 0x8b3) & 0xfb |
         (byte)((((uint)*(byte *)(param_2 + 0x8b5) << 0x1d) >> 0x1f) << 2);
    *(ushort *)(param_2 + 0x8b2) =
         *(ushort *)(param_2 + 0x8b2) & 0xfe7f |
         (ushort)((((uint)*(ushort *)(param_2 + 0x8b4) << 0x17) >> 0x1e) << 7);
    bVar2 = *(byte *)(param_2 + 0x8b3);
    bVar10 = *(byte *)(param_2 + 0x8b5) & 0xe0;
    *(byte *)(param_2 + 0x8b3) = bVar2 & 0x1f | bVar10;
    *(byte *)(param_2 + 0x8b2) = *(byte *)(param_2 + 0x8b2) & 0xc0 | bVar4;
    *(byte *)(param_2 + 0x8b3) =
         bVar2 & 0x1d | bVar10 | (byte)((((uint)*(byte *)(param_2 + 0x8b5) << 0x1e) >> 0x1f) << 1);
  }
  else {
LAB_0012c43c:
    *(byte *)(param_2 + 0x8b3) =
         *(byte *)(param_2 + 0x8b3) & 0xfb |
         (byte)((((uint)*(byte *)(param_2 + 0x8b5) << 0x1d) >> 0x1f) << 2);
    *(ushort *)(param_2 + 0x8b2) =
         *(ushort *)(param_2 + 0x8b2) & 0xfe7f |
         (ushort)((((uint)*(ushort *)(param_2 + 0x8b4) << 0x17) >> 0x1e) << 7);
    bVar2 = *(byte *)(param_2 + 0x8b3);
    bVar10 = *(byte *)(param_2 + 0x8b5) & 0xe0;
    *(byte *)(param_2 + 0x8b3) = bVar2 & 0x1f | bVar10;
    *(byte *)(param_2 + 0x8b2) = *(byte *)(param_2 + 0x8b2) & 0xc0 | bVar4;
    *(byte *)(param_2 + 0x8b3) =
         bVar2 & 0x1d | bVar10 | (byte)((((uint)*(byte *)(param_2 + 0x8b5) << 0x1e) >> 0x1f) << 1);
    if (cVar8 != -1) {
      *(undefined1 *)(param_2 + 0x8b0) = 0;
      goto LAB_0012c4b8;
    }
  }
  *(undefined1 *)(param_2 + 0x8b0) = 1;
LAB_0012c4b8:
  uVar3 = *(ushort *)(param_2 + 0x18);
  if ((uVar3 & 0x20) != 0) {
    *(undefined1 *)(param_2 + 0x8a3) = 1;
    if (*(int *)(param_2 + 0x14) == 2 || *(int *)(param_2 + 0x14) == 0x100) {
      uVar5 = wlan_operate_get_vht_bw(param_2);
      *(undefined1 *)(param_2 + 0x8a4) = uVar5;
    }
    else {
      rtmp_set_vht(param_1,param_2,param_2 + 0x891);
    }
    if (*(char *)(param_2 + 0x8a3) == '\x01') {
      *(byte *)(param_2 + 0x8b5) = *(byte *)(param_2 + 0x8b5) & 0x1f | 0x80;
      uVar9 = (uint)*(byte *)(param_2 + 0x8a4);
      if (uVar9 == 0) {
        if ((*(ushort *)(param_2 + 0x8b2) & 0x180) == 0) {
          bVar10 = 8;
        }
        else {
          bVar10 = 9;
        }
        *(byte *)(param_2 + 0x8b4) = *(byte *)(param_2 + 0x8b4) & 0xc0 | bVar10;
      }
      else if (uVar9 == 1) {
        uVar3 = *(ushort *)(param_2 + 0x8b4);
        *(ushort *)(param_2 + 0x8b4) = uVar3 & 0xfe7f | 0x100;
        *(byte *)(param_2 + 0x8b4) = (byte)uVar3 & 0x40 | 9;
      }
      else if (uVar9 - 2 < 2) {
        uVar3 = *(ushort *)(param_2 + 0x8b4);
        *(ushort *)(param_2 + 0x8b4) = uVar3 | 0x180;
        *(byte *)(param_2 + 0x8b4) = (byte)uVar3 & 0xc0 | 0x89;
      }
      uVar9 = wlan_config_get_vht_sgi(param_2);
      *(byte *)(param_2 + 0x8b5) = *(byte *)(param_2 + 0x8b5) & 0xfd | (byte)((uVar9 & 1) << 1);
      *(ushort *)(param_2 + 0x8b2) =
           *(ushort *)(param_2 + 0x8b2) & 0xfe7f |
           (ushort)((((uint)*(ushort *)(param_2 + 0x8b4) << 0x17) >> 0x1e) << 7);
      *(byte *)(param_2 + 0x8b3) =
           *(byte *)(param_2 + 0x8b3) & 0x1f | *(byte *)(param_2 + 0x8b5) & 0xe0;
      *(byte *)(param_2 + 0x8b2) =
           *(byte *)(param_2 + 0x8b2) & 0xc0 | *(byte *)(param_2 + 0x8b4) & 0x3f;
      *(byte *)(param_2 + 0x8b3) = *(byte *)(param_2 + 0x8b3) & 0xfd | (byte)((uVar9 & 1) << 1);
    }
    uVar3 = *(ushort *)(param_2 + 0x18);
  }
  if ((uVar3 & 0x1c0) != 0) {
    *(byte *)(param_2 + 0x8b5) = *(byte *)(param_2 + 0x8b5) & 0x1f | 0xa0;
    *(byte *)(param_2 + 0x8b4) = *(byte *)(param_2 + 0x8b4) & 0xc0 | 0xb;
    *(byte *)(param_2 + 0x8b3) = *(byte *)(param_2 + 0x8b3) & 0x1f | 0xa0;
    *(byte *)(param_2 + 0x8b2) = *(byte *)(param_2 + 0x8b2) & 0xc0 | 0xb;
  }
  if (((3 < DebugLevel) &&
      (printk(" %s():<---.AMsduSize = %d\n","MlmeUpdateHtTxRates",
              ((uint)local_30[1] << 0x1c) >> 0x1f), 3 < DebugLevel)) &&
     (printk("TX: MCS[0] = %x (choose %d), BW = %d, ShortGI = %d, MODE = %d,\n",
             *(undefined1 *)(iVar7 + 2),*(byte *)(param_2 + 0x8b2) & 0x3f,
             ((uint)*(ushort *)(param_2 + 0x8b2) << 0x17) >> 0x1e,
             ((uint)*(byte *)(param_2 + 0x8b3) << 0x1e) >> 0x1f,*(byte *)(param_2 + 0x8b3) >> 5),
     3 < DebugLevel)) {
    printk("%s():<===\n","MlmeUpdateHtTxRates");
    return;
  }
  return;
}

