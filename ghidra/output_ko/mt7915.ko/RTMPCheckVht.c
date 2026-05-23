// module: mt7915.ko
// function: RTMPCheckVht @ 0x201cc4
// size: 500 bytes
//

undefined4 RTMPCheckVht(int param_1,uint param_2,byte *param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  int iVar7;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar3 = HcGetMaxStaNum(param_1);
  if (uVar3 <= param_2) {
    return 0;
  }
  iVar7 = param_2 * 0x14c0 + param_1;
  iVar4 = GetStaCfgByWdev(param_1,*(undefined4 *)(iVar7 + 0xa1d28));
  *(uint *)(iVar7 + 0xa1dd4) = *(uint *)(iVar7 + 0xa1dd4) | 0x8000000;
  iVar5 = wlan_config_get_vht_sgi(*(undefined4 *)(iVar7 + 0xa1d28));
  if (iVar5 == 1) {
    bVar6 = *param_3;
    if ((bVar6 & 0x20) != 0) {
      *(uint *)(iVar7 + 0xa1dd4) = *(uint *)(iVar7 + 0xa1dd4) | 0x10000;
      bVar6 = *param_3;
    }
    if ((bVar6 & 0x40) != 0) {
      iVar5 = param_2 * 0x14c0 + param_1;
      *(uint *)(iVar5 + 0xa1dd4) = *(uint *)(iVar5 + 0xa1dd4) | 0x20000;
    }
  }
  iVar7 = param_2 * 0x14c0 + param_1;
  iVar5 = wlan_config_get_vht_stbc(*(undefined4 *)(iVar7 + 0xa1d28));
  if (iVar5 != 0) {
    if ((*param_3 & 0x80) != 0) {
      *(uint *)(iVar7 + 0xa1dd4) = *(uint *)(iVar7 + 0xa1dd4) | 0x40000;
    }
    if ((param_3[1] & 7) != 0) {
      iVar5 = param_2 * 0x14c0 + param_1;
      *(uint *)(iVar5 + 0xa1dd4) = *(uint *)(iVar5 + 0xa1dd4) | 0x80000;
    }
  }
  iVar7 = param_2 * 0x14c0 + param_1;
  iVar5 = wlan_config_get_vht_ldpc(*(undefined4 *)(iVar7 + 0xa1d28));
  if (((iVar5 != 0) && ((*(uint *)(iVar2 + 0x2c) & 0x40) != 0)) && ((*param_3 & 0x10) != 0)) {
    *(uint *)(iVar7 + 0xa1dd4) = *(uint *)(iVar7 + 0xa1dd4) | 0x800000;
  }
  __memzero(iVar4 + 0x41d0,8);
  iVar7 = param_2 * 0x14c0 + param_1;
  uVar1 = wlan_operate_get_rx_stream(*(undefined4 *)(iVar7 + 0xa1d28));
  *(ushort *)(iVar4 + 0x41d2) =
       *(ushort *)(iVar4 + 0x41d2) & 0xe000 | (uVar1 & 0x1fff) * 0x145 & 0x1fff;
  iVar5 = wlan_operate_get_tx_stream(*(undefined4 *)(iVar7 + 0xa1d28));
  *(ushort *)(iVar4 + 0x41d6) =
       *(ushort *)(iVar4 + 0x41d6) & 0xe000 |
       (ushort)((uint)(iVar5 << 0x13) >> 0x13) * 0x145 & 0x1fff;
  if (*(char *)(iVar2 + 0x96) != '\0') {
    mt_WrapSetVHTETxBFCap(param_1,*(undefined4 *)(iVar7 + 0xa1d28),iVar4 + 0x41cc);
    return 1;
  }
  return 1;
}

