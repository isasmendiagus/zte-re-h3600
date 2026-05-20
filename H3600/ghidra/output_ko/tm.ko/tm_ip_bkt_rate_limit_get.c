// module: tm.ko
// function: tm_ip_bkt_rate_limit_get @ 0x51df0
// size: 136 bytes
//

undefined4 tm_ip_bkt_rate_limit_get(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  int iVar1;
  int local_18;
  uint local_14;
  
  local_18 = 0;
  local_14 = 0;
  iVar1 = sadm_get_indtbl_ip_vlan_tfcfg_table(param_1,&local_18);
  if (iVar1 == 0) {
    *(bool *)param_2 = local_18 != 0;
    iVar1 = sadm_get_ip_vlan_token_bucket_fill_spd(param_1,&local_14);
    if (iVar1 == 0) {
      if ((local_14 & 0x3f) == 0) {
        *param_3 = local_14;
        return 0;
      }
      *param_3 = local_14 + 1;
      return 0;
    }
  }
  printk("tm_ip_bkt_rate_limit_get fail\n");
  return 0xffffffff;
}

