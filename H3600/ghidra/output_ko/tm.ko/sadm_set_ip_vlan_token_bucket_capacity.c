// module: tm.ko
// function: sadm_set_ip_vlan_token_bucket_capacity @ 0x26bc0
// size: 316 bytes
//

undefined4 sadm_set_ip_vlan_token_bucket_capacity(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  uint local_18;
  uint local_14;
  
  bVar3 = 0x3e < param_1;
  if (param_1 < 0x40) {
    bVar3 = 0x1fffff < param_2;
  }
  if (bVar3) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_14813,"sadm_set_ip_vlan_token_bucket_capacity"), iVar2 != 0)) {
      printk("[TM][sadm_set_ip_vlan_token_bucket_capacity]input invalid parameter!\n");
    }
    uVar1 = 1;
  }
  else {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_set_ip_vlan_token_bucket_capacity]input:bucket_id = %d,capacity = %d\n",
             param_1,param_2);
    }
    sadm_set_indreg_rd_cfg(param_1,0,"sadm_set_ip_vlan_token_bucket_capacity");
    sadm_get_indacs_dat(&local_18,0);
    sadm_get_indacs_dat(&local_14,1);
    sadm_set_indreg_wr_cfg(param_1,0,"sadm_set_ip_vlan_token_bucket_capacity");
    sadm_set_indacs_dat(local_14 | param_2 >> 2,1);
    iVar2 = sadm_set_indacs_dat(local_18 & 0x3fffffff | param_2 << 0x1e,0);
    uVar1 = 0;
    if (iVar2 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_14816,"sadm_set_ip_vlan_token_bucket_capacity"), iVar2 != 0)) {
        printk("[TM][sadm_set_ip_vlan_token_bucket_capacity]write reg failed!\n");
      }
      return 0xffffffff;
    }
  }
  return uVar1;
}

