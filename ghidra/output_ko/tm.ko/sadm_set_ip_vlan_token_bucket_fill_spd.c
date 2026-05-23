// module: tm.ko
// function: sadm_set_ip_vlan_token_bucket_fill_spd @ 0x26550
// size: 296 bytes
//

undefined4 sadm_set_ip_vlan_token_bucket_fill_spd(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  bool bVar7;
  uint local_1c [2];
  
  bVar7 = 0x1ffffffe < param_2;
  bVar6 = param_2 == 0x1fffffff;
  if (param_2 < 0x20000000) {
    bVar7 = 0x3e < param_1;
    bVar6 = param_1 == 0x3f;
  }
  if (!bVar7 || bVar6) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_set_ip_vlan_token_bucket_fill_spd]input:bucket_id = %d,speed = %d\n",param_1
             ,param_2);
    }
    iVar5 = sadm_set_indreg_rd_cfg(param_1,0,"sadm_set_indtbl_token_bucket_fill_spd");
    iVar2 = sadm_get_indacs_dat(local_1c,0);
    iVar3 = sadm_set_indreg_wr_cfg(param_1,0,"sadm_set_indtbl_token_bucket_fill_spd");
    iVar4 = sadm_set_indacs_dat(local_1c[0] & 0xc0000003 | param_2 << 2,0);
    uVar1 = 0;
    if (((iVar2 != 0 || iVar5 != 0) || iVar3 != 0) || iVar4 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar5 = ___ratelimit(_rs_14738,"sadm_set_ip_vlan_token_bucket_fill_spd"), iVar5 != 0)) {
        printk("[TM][sadm_set_ip_vlan_token_bucket_fill_spd]write reg failed!\n");
      }
      return 0xffffffff;
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar5 = ___ratelimit(_rs_14735,"sadm_set_ip_vlan_token_bucket_fill_spd"), iVar5 != 0)) {
      printk("[TM][sadm_set_ip_vlan_token_bucket_fill_spd]input invalid parameter!\n");
    }
    uVar1 = 1;
  }
  return uVar1;
}

