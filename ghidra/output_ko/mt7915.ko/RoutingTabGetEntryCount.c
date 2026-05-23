// module: mt7915.ko
// function: RoutingTabGetEntryCount @ 0xa10ac
// size: 116 bytes
//

int RoutingTabGetEntryCount(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 <= param_2 || 0x1f < param_2) {
    return 0;
  }
  param_1 = param_2 * 0x5834 + param_1;
  iVar2 = 0;
  if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"[param_1 + 0x41] != '\0'
     ) {
    iVar2 = 0x100 - (uint)(byte)"RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n"
                                [param_1 + 0x14];
  }
  return iVar2;
}

