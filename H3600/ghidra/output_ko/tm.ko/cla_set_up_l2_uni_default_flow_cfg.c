// module: tm.ko
// function: cla_set_up_l2_uni_default_flow_cfg @ 0x11f64
// size: 424 bytes
//

undefined4 cla_set_up_l2_uni_default_flow_cfg(uint param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  
  if ((6 < g_tm_debug_level) &&
     (printk("[TM][cla_set_up_l2_uni_default_flow_cfg]input:\n"), 6 < g_tm_debug_level)) {
    printk("uni_id = %d, del_en = %d, pkt_change_len = %d, gemport_valid = %d, gemport_id/default_uni_port = %d, tcontid_llid = %d, queue_id = %d, flow_id = %d\n"
           ,param_1,*param_2,param_2[1],param_2[2],param_2[3],param_2[4],param_2[5],param_2[6]);
  }
  if ((((*param_2 < 2) && (param_2[1] < 4)) && (param_2[2] < 2)) &&
     ((param_2[4] < 0x28 && (param_2[5] < 8)))) {
    bVar5 = 6 < param_1;
    if (param_1 < 8) {
      bVar5 = 0x1ff < param_2[6];
    }
    if (!bVar5) {
      uVar4 = param_2[3];
      if (param_2[2] == 0) {
        if (uVar4 < 0x20) goto LAB_00012000;
      }
      else if (uVar4 < 0x1000) {
LAB_00012000:
        iVar1 = tmOnuRegWrite(0x17,*param_2 * -0x80000000 + param_2[1] * 0x20000000 + param_2[6] +
                                   uVar4 * 0x20000 + param_2[5] * 0x200 +
                                   (param_2[4] & 0x1f) * 0x1000,param_1,&claRegTable);
        iVar2 = tmOnuRegWrite(0x18,param_2[2],param_1,&claRegTable);
        iVar3 = tmOnuRegWrite(0x19,(param_2[4] << 0x1a) >> 0x1f,param_1,&claRegTable);
        if ((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) {
          return 0;
        }
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][cla_set_up_l2_uni_default_flow_cfg]reg write failed\n");
        return 0xffffffff;
      }
    }
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_set_up_l2_uni_default_flow_cfg]input invalid parameter!\n");
  }
  return 1;
}

