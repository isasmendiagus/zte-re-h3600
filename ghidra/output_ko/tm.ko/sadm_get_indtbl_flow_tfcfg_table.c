// module: tm.ko
// function: sadm_get_indtbl_flow_tfcfg_table @ 0x25ccc
// size: 460 bytes
//

undefined4 sadm_get_indtbl_flow_tfcfg_table(uint param_1,uint param_2,uint *param_3)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  bool bVar4;
  uint local_1c [2];
  
  bVar4 = 6 < param_2;
  bVar3 = param_2 == 7;
  if (param_2 < 8) {
    bVar4 = 0xf < param_1;
    bVar3 = param_1 == 0x10;
  }
  local_1c[0] = 0;
  if ((bVar4 && !bVar3) || (param_2 == 0 && 6 < param_1)) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sadm_get_indtbl_flow_tfcfg_table]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_get_indtbl_flow_tfcfg_table]input:inport_id = %d\n",param_1);
  }
  switch(param_2) {
  case 1:
    param_1 = param_1 + 0x10;
    uVar2 = 0;
    break;
  case 2:
    printk("ERROR\n");
    uVar2 = 0;
    param_1 = 0;
    break;
  case 3:
    uVar2 = 1;
    break;
  case 4:
    param_1 = param_1 + 0x20;
    uVar2 = 1;
    break;
  case 5:
    uVar2 = 2;
    break;
  case 7:
    param_1 = param_1 + 0x10;
  case 6:
    uVar2 = 3;
    break;
  default:
    param_1 = param_1 + 1;
    uVar2 = 0;
  }
  iVar1 = sadm_set_indreg_rd_cfg(param_1,uVar2,"sadm_get_indtbl_flow_tfcfg_table");
  if (iVar1 == 0) {
    iVar1 = sadm_get_indacs_dat(local_1c);
    if (iVar1 == 0) {
      *param_3 = local_1c[0] & 1;
      if (6 < g_tm_debug_level) {
        printk("[TM][sadm_get_indtbl_flow_tfcfg_table]output:en = %d\n");
        return 0;
      }
      return 0;
    }
    if (g_tm_debug_level != 0) {
      iVar1 = ___ratelimit(_rs_14651,"sadm_get_indtbl_flow_tfcfg_table");
      if (iVar1 != 0) {
        printk("[TM][sadm_get_indtbl_flow_tfcfg_table]write reg failed!\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_14648,"sadm_get_indtbl_flow_tfcfg_table"), iVar1 != 0)) {
    printk("[TM][sadm_set_indtbl_flow_tfcfg_table]write reg failed!\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

