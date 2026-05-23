// module: tm.ko
// function: cla_set_config @ 0x10750
// size: 528 bytes
//

undefined4 cla_set_config(uint *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((((6 < g_tm_debug_level) && (printk("[TM][cla_set_config]input:\n"), 6 < g_tm_debug_level)) &&
      (printk("age_rd_clear = %d, trap_acl_en = %d, modify_en = %d,up_unicast_ctrl = %d,  \n",
              *param_1,param_1[1],param_1[2],param_1[3]), 6 < g_tm_debug_level)) &&
     (printk("dn_unicast_ctrl = %d, dn_multicast_ctrl = %d,dn_broadcast_ctrl = %d,mac_req_ctrl = %d, \n"
             ,param_1[4],param_1[5],param_1[6],param_1[7]), 6 < g_tm_debug_level)) {
    printk("v6rd_del_en = %d, dslite_del_en = %d, age_mode = %d,outport_sel_en = %d, local_ip_mode_dn = %d,local_ip_mode_up = %d \n"
           ,param_1[8],param_1[9],param_1[10],param_1[0xb],param_1[0xc],param_1[0xd]);
  }
  if (((((*param_1 < 2) && (param_1[1] < 2)) &&
       ((param_1[2] < 2 && ((param_1[3] < 2 && (param_1[4] < 2)))))) && (param_1[5] < 2)) &&
     (((((param_1[6] < 2 && (param_1[7] < 2)) && (param_1[8] < 2)) &&
       ((param_1[9] < 2 && (param_1[10] < 2)))) &&
      ((param_1[0xb] < 2 && ((param_1[0xc] < 2 && (param_1[0xd] < 2)))))))) {
    iVar2 = tmOnuRegWrite(3,param_1[1] * 0x20000 + *param_1 * 0x80000 + param_1[0xd] +
                            param_1[2] * 0x10000 + param_1[3] * 0x8000 + param_1[4] * 0x4000 +
                            param_1[5] * 0x2000 + param_1[6] * 0x1000 + param_1[7] * 0x800 +
                            param_1[8] * 0x400 + param_1[9] * 0x200 + param_1[10] * 8 +
                            param_1[0xb] * 4 + param_1[0xc] * 2,0,&claRegTable);
    uVar1 = 0;
    if (iVar2 != 0) {
      if (g_tm_debug_level == 0) {
        uVar1 = 0xffffffff;
      }
      else {
        printk("[TM][cla_set_config]reg write failed\n");
        uVar1 = 0xffffffff;
      }
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][cla_set_config]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

