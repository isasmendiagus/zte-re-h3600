// module: tm.ko
// function: sadm_get_ip_vlan_token_bucket_fill_spd @ 0x26684
// size: 308 bytes
//

undefined4 sadm_get_ip_vlan_token_bucket_fill_spd(uint param_1,uint *param_2)

{
  int iVar1;
  int local_14;
  
  local_14 = 0;
  if (0x3f < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sadm_get_ip_vlan_token_bucket_fill_spd]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_get_ip_vlan_token_bucket_fill_spd]input:bucket_id = %d\n",param_1);
  }
  iVar1 = sadm_set_indreg_rd_cfg(param_1,0,"sadm_get_ip_vlan_token_bucket_fill_spd");
  if (iVar1 == 0) {
    iVar1 = sadm_get_indacs_dat(&local_14);
    if (iVar1 == 0) {
      *param_2 = (uint)(local_14 << 2) >> 4;
      if (6 < g_tm_debug_level) {
        printk("[TM][sadm_get_ip_vlan_token_bucket_fill_spd]output:speed = %d\n");
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar1 = ___ratelimit(_rs_14749,"sadm_get_ip_vlan_token_bucket_fill_spd");
  }
  else {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar1 = ___ratelimit(_rs_14746,"sadm_get_ip_vlan_token_bucket_fill_spd");
  }
  if (iVar1 != 0) {
    printk("[TM][sadm_get_ip_vlan_token_bucket_fill_spd]write reg failed!\n");
  }
  return 0xffffffff;
}

