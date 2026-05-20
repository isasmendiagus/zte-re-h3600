// module: mt7915.ko
// function: RoutingEntryRefresh @ 0xa0578
// size: 128 bytes
//

void RoutingEntryRefresh(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 <= param_2 || 0x1f < param_2) {
    return;
  }
  if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"
      [param_2 * 0x5834 + param_1 + 0x41] != '\0' && param_3 != 0) {
    *(int *)(param_3 + 8) = jiffies + 6000;
    return;
  }
  return;
}

