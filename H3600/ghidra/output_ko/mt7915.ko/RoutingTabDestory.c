// module: mt7915.ko
// function: RoutingTabDestory @ 0xa09dc
// size: 236 bytes
//

void RoutingTabDestory(int param_1,uint param_2,uint param_3)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar2 <= param_2 || 0x1f < param_2) {
    return;
  }
  iVar3 = param_2 * 0x5834 + param_1;
  if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"[iVar3 + 0x41] != '\0')
  {
    RoutingTabClear(param_1,param_2,param_3);
    uVar2 = *(uint *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar3);
    *(uint *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar3) =
         uVar2 & ~param_3;
    if ((uVar2 & ~param_3) == 0) {
      if (*(int *)("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar3 + 8) != 0)
      {
        os_free_mem();
        pcVar1 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + iVar3 + 8;
        pcVar1[0] = '\0';
        pcVar1[1] = '\0';
        pcVar1[2] = '\0';
        pcVar1[3] = '\0';
      }
      param_1 = param_2 * 0x5834 + param_1;
      pcVar1 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + param_1 + 0x10;
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      pcVar1 = "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" + param_1 + 0xc;
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      "RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"[param_1 + 0x14] = '\0';
      "RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"[param_1 + 0x41] = '\0';
      return;
    }
    return;
  }
  return;
}

