// module: mt7915.ko
// function: ApCheckAccessControlList @ 0x154f0
// size: 388 bytes
//

undefined4 ApCheckAccessControlList(int param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *__s2;
  bool bVar5;
  uint local_15c;
  undefined4 local_158;
  undefined2 local_154;
  
  uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 <= param_3 || 0x1f < param_3) {
    return 0;
  }
  iVar3 = param_1 + param_3 * 0x5834;
  if (*(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" + iVar3 + 0x31) != 0) {
    bVar5 = *(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" + iVar3 + 0x31) != 1;
    iVar3 = *(int *)("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" + iVar3 + 1);
    if (iVar3 != 0) {
      __s2 = "Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" + param_1 + param_3 * 0x5834 + 5;
      iVar4 = 0;
      do {
        iVar4 = iVar4 + 1;
        iVar2 = memcmp(param_2,__s2,6);
        __s2 = __s2 + 8;
        if (iVar2 == 0) {
          bVar5 = !bVar5;
          break;
        }
      } while (iVar4 != iVar3);
    }
    if (!bVar5) {
      if (2 < DebugLevel) {
        printk("%02x:%02x:%02x:%02x:%02x:%02x failed in ACL checking\n",*(undefined1 *)param_2,
               *(undefined1 *)((int)param_2 + 1),*(undefined1 *)((int)param_2 + 2),
               *(undefined1 *)((int)param_2 + 3),*(undefined1 *)(param_2 + 1),
               *(undefined1 *)((int)param_2 + 5));
      }
      if ((*(uint *)(param_1 + 0xa7d168) & 2) == 0) {
        return 0;
      }
      __memzero(&local_15c,0x134);
      local_158 = *param_2;
      local_154 = *(undefined2 *)(param_2 + 1);
      local_15c = param_3;
      Kernel_ASEND("cspd.wlan_manage.wlan_mgr",0xa23e,&local_15c,0x134,0,0);
      return 0;
    }
  }
  return 1;
}

