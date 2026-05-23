// module: tm.ko
// function: cla_set_up_l3_default_flow_cfg @ 0x125e0
// size: 400 bytes
//

undefined4 cla_set_up_l3_default_flow_cfg(uint *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if ((6 < g_tm_debug_level) &&
     (printk("[TM][cla_set_up_l3_default_flow_cfg]input:\n"), 6 < g_tm_debug_level)) {
    printk("del_en = %d, pkt_change_len = %d, gemport_valid = %d, gemport_id/default_uni_port = %d, tcontid_llid = %d, queue_id = %d, flow_id = %d\n"
           ,*param_1,param_1[1],param_1[2],param_1[3],param_1[4],param_1[5],param_1[6]);
  }
  if ((((*param_1 < 2) && (param_1[1] < 4)) && (param_1[2] < 2)) &&
     (((param_1[4] < 0x28 && (param_1[5] < 8)) && (param_1[6] < 0x200)))) {
    uVar4 = param_1[3];
    if (param_1[2] == 0) {
      if (uVar4 < 0x20) goto LAB_00012674;
    }
    else if (uVar4 < 0x1000) {
LAB_00012674:
      iVar1 = tmOnuRegWrite(0x1e,*param_1 * -0x80000000 + param_1[1] * 0x20000000 + param_1[6] +
                                 param_1[5] * 0x200 + (param_1[4] & 0x1f) * 0x1000 + uVar4 * 0x20000
                            ,0,&claRegTable);
      iVar2 = tmOnuRegWrite(0x1f,param_1[2],0,&claRegTable);
      iVar3 = tmOnuRegWrite(0x20,(param_1[4] << 0x1a) >> 0x1f,0,&claRegTable);
      if ((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) {
        return 0;
      }
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][cla_set_up_l3_default_flow_cfg]reg write failed\n");
      return 0xffffffff;
    }
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_set_up_l3_default_flow_cfg]input invalid parameter!\n");
  }
  return 1;
}

