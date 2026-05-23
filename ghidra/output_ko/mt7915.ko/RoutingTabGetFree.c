// module: mt7915.ko
// function: RoutingTabGetFree @ 0xa0494
// size: 228 bytes
//

int * RoutingTabGetFree(int param_1,uint param_2)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar2 <= param_2 || 0x1f < param_2) {
    return (int *)0x0;
  }
  iVar5 = param_1 + param_2 * 0x5834;
  if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"[iVar5 + 0x41] == '\0')
  {
    return (int *)0x0;
  }
  _raw_spin_lock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                    param_1 + param_2 * 0x5834 + 4);
  piVar4 = *(int **)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0xc);
  if (piVar4 != (int *)0x0) {
    iVar3 = *piVar4;
    *(int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0xc) = iVar3;
    if (iVar3 == 0) {
      pcVar1 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar5 + 0x10;
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
    }
    "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"
    [param_2 * 0x5834 + param_1 + 0x14] =
         "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"
         [param_2 * 0x5834 + param_1 + 0x14] + -1;
  }
  _raw_spin_unlock_bh("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
                      param_1 + param_2 * 0x5834 + 4);
  return piVar4;
}

