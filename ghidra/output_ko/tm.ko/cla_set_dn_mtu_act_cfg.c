// module: tm.ko
// function: cla_set_dn_mtu_act_cfg @ 0x11828
// size: 200 bytes
//

undefined4
cla_set_dn_mtu_act_cfg(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_dn_mtu_act_cfg]input: length_val = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (3 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7712,"cla_set_dn_mtu_act_cfg"), iVar1 != 0)) {
      printk("[TM][cla_set_dn_mtu_act_cfg]input invalid parameter!\n");
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x11,param_1,0,&claRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_7715,"cla_set_dn_mtu_act_cfg"), iVar1 != 0)) {
    printk("[TM][cla_set_dn_mtu_act_cfg]reg write failed\n");
  }
  return 0xffffffff;
}

