// module: tm.ko
// function: tm_ip_bkt_rate_limit_set @ 0x51d00
// size: 240 bytes
//

undefined4 tm_ip_bkt_rate_limit_set(uint param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  int local_18;
  int local_14;
  
  local_18 = 5;
  local_14 = 5;
  sadm_get_dn_tf_mode(&local_18);
  iVar1 = sadm_get_up_tf_mode(&local_14);
  if (iVar1 == 0) {
    if (local_18 == 3) {
      bVar3 = param_1 == 0xd;
      if (param_1 < 0xe) {
        bVar3 = local_14 == 1;
      }
      if (bVar3) {
        printk("while up uniport rate limit mode,input bucket_id unable less than 13!\n");
        return 0xffffffff;
      }
    }
    iVar1 = sadm_set_indtbl_ip_vlan_tfcfg_table(param_1,param_2 != 0);
    if (((iVar1 == 0) && (iVar1 = sadm_set_bucket_fill_time(0x1869), iVar1 == 0)) &&
       (iVar1 = sadm_set_ip_vlan_token_bucket_fill_spd(param_1,param_3), iVar1 == 0)) {
      uVar2 = tm_getFillcap(param_3);
      iVar1 = sadm_set_ip_vlan_token_bucket_capacity(param_1,uVar2);
      if (iVar1 == 0) {
        return 0;
      }
    }
    printk("tm_vlan_bkt_rate_limit_set fail\n");
  }
  else {
    printk("spa get up dn traffic mode fail\n");
  }
  return 0xffffffff;
}

