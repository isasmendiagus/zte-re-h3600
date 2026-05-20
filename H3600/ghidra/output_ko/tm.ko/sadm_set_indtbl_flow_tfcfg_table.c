// module: tm.ko
// function: sadm_set_indtbl_flow_tfcfg_table @ 0x25ae4
// size: 448 bytes
//

undefined4 sadm_set_indtbl_flow_tfcfg_table(uint param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  bool bVar7;
  bool bVar8;
  uint local_1c;
  
  bVar8 = param_3 != 0;
  bVar7 = param_3 == 1;
  if (param_3 < 2) {
    bVar8 = 0xe < param_1;
    bVar7 = param_1 == 0xf;
  }
  local_1c = 0;
  if ((7 < param_2 || bVar8 && !bVar7) || (param_2 == 0 && 6 < param_1)) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_14614,"sadm_set_indtbl_flow_tfcfg_table"), iVar2 != 0)) {
      printk("[TM][sadm_set_indtbl_flow_tfcfg_table]input invalid parameter!\n");
    }
    uVar1 = 1;
  }
  else {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_set_indtbl_flow_tfcfg_table]input:inport_id = %d,en = %d\n",param_1);
    }
    switch(param_2) {
    case 1:
      param_1 = param_1 + 0x10;
      uVar1 = 0;
      break;
    case 2:
      uVar1 = 0;
      param_1 = 0;
      printk("ERROR\n");
      break;
    case 3:
      uVar1 = 1;
      break;
    case 4:
      param_1 = param_1 + 0x20;
      uVar1 = 1;
      break;
    case 5:
      uVar1 = 2;
      break;
    case 7:
      param_1 = param_1 + 0x10;
    case 6:
      uVar1 = 3;
      break;
    default:
      param_1 = param_1 + 1;
      uVar1 = 0;
    }
    iVar2 = sadm_set_indreg_rd_cfg(param_1,uVar1,"sadm_set_indtbl_flow_tfcfg_table");
    iVar3 = sadm_get_indacs_dat(&local_1c,0);
    uVar6 = local_1c & 0xfffffffe;
    iVar4 = sadm_set_indreg_wr_cfg(param_1,uVar1,"sadm_set_indtbl_flow_tfcfg_table");
    iVar5 = sadm_set_indacs_dat(param_3 | uVar6,0);
    uVar1 = 0;
    if (((iVar3 != 0 || iVar2 != 0) || iVar4 != 0) || iVar5 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_14627,"sadm_set_indtbl_flow_tfcfg_table"), iVar2 != 0)) {
        printk("[TM][sadm_set_indtbl_flow_tfcfg_table]write reg failed!\n");
      }
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

