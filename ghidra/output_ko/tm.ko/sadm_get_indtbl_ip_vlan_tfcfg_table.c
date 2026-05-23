// module: tm.ko
// function: sadm_get_indtbl_ip_vlan_tfcfg_table @ 0x25ffc
// size: 308 bytes
//

undefined4 sadm_get_indtbl_ip_vlan_tfcfg_table(uint param_1,uint *param_2)

{
  int iVar1;
  uint local_14;
  
  local_14 = 0;
  if (0x3f < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sadm_get_indtbl_ip_vlan_tfcfg_table]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_get_indtbl_ip_vlan_tfcfg_table]input:bucket_id = %d\n",param_1);
  }
  iVar1 = sadm_set_indreg_rd_cfg(param_1,0,"sadm_get_indtbl_ip_vlan_tfcfg_table");
  if (iVar1 == 0) {
    iVar1 = sadm_get_indacs_dat(&local_14);
    if (iVar1 == 0) {
      *param_2 = local_14 & 1;
      if (6 < g_tm_debug_level) {
        printk("[TM][sadm_get_indtbl_ip_vlan_tfcfg_table]output:en = %d\n");
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar1 = ___ratelimit(_rs_14674,"sadm_get_indtbl_ip_vlan_tfcfg_table");
  }
  else {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    iVar1 = ___ratelimit(_rs_14671,"sadm_get_indtbl_ip_vlan_tfcfg_table");
  }
  if (iVar1 != 0) {
    printk("[TM][sadm_get_indtbl_ip_vlan_tfcfg_table]write reg failed!\n");
  }
  return 0xffffffff;
}

