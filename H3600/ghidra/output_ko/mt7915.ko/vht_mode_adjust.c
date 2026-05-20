// module: mt7915.ko
// function: vht_mode_adjust @ 0x2028d8
// size: 504 bytes
//

undefined4 vht_mode_adjust(int param_1,int param_2,byte *param_3,char *param_4)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  ushort uVar5;
  int iVar6;
  uint uVar7;
  
  iVar6 = *(int *)(param_2 + 8);
  *(byte *)(param_2 + 0xbf) = *(byte *)(param_2 + 0xbf) & 0x1f | 0x80;
  *(uint *)(param_2 + 100) = *(uint *)(param_2 + 100) | 4;
  if (iVar6 == 0) {
    return 0;
  }
  wlan_operate_get_addht(iVar6);
  iVar2 = HcGetBandByWdev(*(undefined4 *)(param_2 + 8));
  *(undefined1 *)(param_1 + iVar2 + 0x285943) = 1;
  uVar3 = wlan_config_get_vht_sgi(iVar6);
  if (((*(ushort *)(param_2 + 0xbe) & 0x180) != 0x80) || (iVar6 = *(int *)(param_2 + 8), iVar6 == 0)
     ) {
    return 1;
  }
  if (3 < DebugLevel) {
    printk("%s: DesiredHtPhyInfo->vht_bw=%d, ch_width=%d\n","vht_mode_adjust",
           *(undefined1 *)(iVar6 + 0x8a4),((uint)*param_3 << 0x1c) >> 0x1e);
  }
  uVar7 = (uint)*(byte *)(iVar6 + 0x8a4);
  if (uVar7 != 0) {
    if ((*param_3 & 0xc) != 0) {
      if (uVar7 == 1) {
        *(ushort *)(param_2 + 0xbe) = *(ushort *)(param_2 + 0xbe) & 0xfe7f | 0x100;
        *(byte *)(param_2 + 0xbf) =
             *(byte *)(param_2 + 0xbf) & 0xfd |
             (byte)((uVar3 & ((uint)*param_3 << 0x1a) >> 0x1f) << 1);
        bVar1 = wlan_config_get_vht_stbc(*(undefined4 *)(param_2 + 8));
        *(byte *)(param_2 + 0xbf) =
             *(byte *)(param_2 + 0xbf) & 0xfb | ((bVar1 & param_3[1] & 7) != 0) << 2;
        return 1;
      }
      if (1 < uVar7 - 2) {
        return 1;
      }
      uVar4 = *(undefined4 *)(param_2 + 8);
      *(ushort *)(param_2 + 0xbe) = *(ushort *)(param_2 + 0xbe) | 0x180;
      *(byte *)(param_2 + 0xbf) =
           *(byte *)(param_2 + 0xbf) & 0xfd |
           (byte)((uVar3 & ((uint)*param_3 << 0x19) >> 0x1f) << 1);
      goto LAB_002029c4;
    }
    if (param_4 == (char *)0x0) {
      uVar5 = *(ushort *)(param_2 + 0xbe);
    }
    else {
      uVar5 = *(ushort *)(param_2 + 0xbe);
      if (*param_4 == '\0') {
        *(ushort *)(param_2 + 0xbe) = uVar5 & 0xfe7f | 0x80;
        goto LAB_002029c0;
      }
    }
    *(ushort *)(param_2 + 0xbe) = uVar5 & 0xfe7f | 0x100;
    *(byte *)(param_2 + 0xbf) =
         *(byte *)(param_2 + 0xbf) & 0xfd | (byte)((uVar3 & ((uint)*param_3 << 0x1a) >> 0x1f) << 1);
  }
LAB_002029c0:
  uVar4 = *(undefined4 *)(param_2 + 8);
LAB_002029c4:
  bVar1 = wlan_config_get_vht_stbc(uVar4);
  *(byte *)(param_2 + 0xbf) =
       *(byte *)(param_2 + 0xbf) & 0xfb | ((bVar1 & param_3[1] & 7) != 0) << 2;
  return 1;
}

