// module: mt7915.ko
// function: check_vht @ 0x201eb8
// size: 228 bytes
//

undefined4 check_vht(int param_1,uint param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar3 = HcGetMaxStaNum(param_1);
  if (uVar3 <= param_2) {
    return 0;
  }
  iVar6 = param_2 * 0x14c0 + param_1;
  iVar4 = GetStaCfgByWdev(param_1,*(undefined4 *)(iVar6 + 0xa1d28));
  __memzero(iVar4 + 0x41d0,8);
  uVar1 = wlan_operate_get_rx_stream(*(undefined4 *)(iVar6 + 0xa1d28));
  *(ushort *)(iVar4 + 0x41d2) =
       *(ushort *)(iVar4 + 0x41d2) & 0xe000 | (uVar1 & 0x1fff) * 0x145 & 0x1fff;
  iVar5 = wlan_operate_get_tx_stream(*(undefined4 *)(iVar6 + 0xa1d28));
  *(ushort *)(iVar4 + 0x41d6) =
       *(ushort *)(iVar4 + 0x41d6) & 0xe000 |
       (ushort)((uint)(iVar5 << 0x13) >> 0x13) * 0x145 & 0x1fff;
  if (*(char *)(iVar2 + 0x96) == '\0') {
    return 1;
  }
  mt_WrapSetVHTETxBFCap(param_1,*(undefined4 *)(iVar6 + 0xa1d28),iVar4 + 0x41cc);
  return 1;
}

