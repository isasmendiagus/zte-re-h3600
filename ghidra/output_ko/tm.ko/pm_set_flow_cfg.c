// module: tm.ko
// function: pm_set_flow_cfg @ 0x353d8
// size: 216 bytes
//

undefined4 pm_set_flow_cfg(uint *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((((*param_1 < 2) && (param_1[1] < 2)) && (param_1[2] < 2)) && (param_1[3] < 2)) {
    iVar1 = pm_set_flow_sta_pkt_len_sel();
    iVar2 = pm_set_flow_sta_read_clear_en(param_1[1]);
    iVar3 = pm_set_flow_sta_cnt_mode(param_1[2]);
    iVar4 = pm_set_flow_sta_fwd_only_en(param_1[3]);
    if (((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) {
      return 0;
    }
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7450,"pm_set_flow_cfg"), iVar1 != 0)) {
      printk("[TM][pm_set_flow_cfg]failed\n");
    }
    return 0xffffffff;
  }
  if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][pm_set_zte_cfg]input invalid parameter!\n");
  return 1;
}

