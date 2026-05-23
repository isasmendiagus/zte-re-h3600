// module: mt7915.ko
// function: GetRoutingTabHead @ 0xa0780
// size: 156 bytes
//

undefined4 GetRoutingTabHead(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 <= param_2 || 0x1f < param_2) {
    return 0;
  }
  if ("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n"
      [param_1 + param_2 * 0x5834 + 0x41] != '\0' && param_3 < 0x40) {
    return *(undefined4 *)
            ("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n" +
            param_1 + param_2 * 0x5834 + param_3 * 0xc + 0x18);
  }
  return 0;
}

