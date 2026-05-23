// module: tm.ko
// function: sadm_get_ip_vlan_token_bucket_capacity @ 0x26d08
// size: 320 bytes
//

undefined4 sadm_get_ip_vlan_token_bucket_capacity(uint param_1,uint *param_2)

{
  int iVar1;
  uint local_18;
  int iStack_14;
  
  if (0x3f < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sadm_get_ip_vlan_token_bucket_capacity]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_get_ip_vlan_token_bucket_capacity]input:bucket_id = %d\n",param_1);
  }
  iVar1 = sadm_set_indreg_rd_cfg(param_1,0,"sadm_get_ip_vlan_token_bucket_capacity");
  if (iVar1 == 0) {
    sadm_get_indacs_dat(&iStack_14,1);
    iVar1 = sadm_get_indacs_dat(&local_18,0);
    if (iVar1 == 0) {
      *param_2 = iStack_14 << 2 | local_18 >> 0x1e;
      if (6 < g_tm_debug_level) {
        printk("[TM][sadm_get_ip_vlan_token_bucket_capacity]output:capacity = %d\n");
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar1 = ___ratelimit(_rs_14828,"sadm_get_ip_vlan_token_bucket_capacity");
  }
  else {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar1 = ___ratelimit(_rs_14825,"sadm_get_ip_vlan_token_bucket_capacity");
  }
  if (iVar1 != 0) {
    printk("[TM][sadm_get_ip_vlan_token_bucket_capacity]write reg failed!\n");
  }
  return 0xffffffff;
}

