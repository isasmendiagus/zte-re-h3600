// module: tm.ko
// function: sadm_set_indtbl_ip_vlan_tfcfg_table @ 0x25ec0
// size: 304 bytes
//

undefined4 sadm_set_indtbl_ip_vlan_tfcfg_table(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  bool bVar7;
  bool bVar8;
  uint local_1c [2];
  
  bVar8 = param_2 != 0;
  bVar7 = param_2 == 1;
  if (param_2 < 2) {
    bVar8 = 0x3e < param_1;
    bVar7 = param_1 == 0x3f;
  }
  local_1c[0] = 0;
  if (!bVar8 || bVar7) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_set_indtbl_ip_vlan_tfcfg_table]input:bucket_id = %d,en = %d\n",param_1,
             param_2);
    }
    iVar5 = sadm_set_indreg_rd_cfg(param_1,0,"sadm_set_indtbl_ip_vlan_tfcfg_table");
    iVar2 = sadm_get_indacs_dat(local_1c,0);
    uVar6 = local_1c[0] & 0xfffffffe;
    iVar3 = sadm_set_indreg_wr_cfg(param_1,0,"sadm_set_indtbl_ip_vlan_tfcfg_table");
    iVar4 = sadm_set_indacs_dat(param_2 | uVar6,0);
    uVar1 = 0;
    if (((iVar2 != 0 || iVar5 != 0) || iVar3 != 0) || iVar4 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar5 = ___ratelimit(_rs_14663,"sadm_set_indtbl_ip_vlan_tfcfg_table"), iVar5 != 0)) {
        printk("[TM][sadm_set_indtbl_ip_vlan_tfcfg_table]write reg failed!\n");
      }
      return 0xffffffff;
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar5 = ___ratelimit(_rs_14660,"sadm_set_indtbl_ip_vlan_tfcfg_table"), iVar5 != 0)) {
      printk("[TM][sadm_set_indtbl_ip_vlan_tfcfg_table]input invalid parameter!\n");
    }
    uVar1 = 1;
  }
  return uVar1;
}

