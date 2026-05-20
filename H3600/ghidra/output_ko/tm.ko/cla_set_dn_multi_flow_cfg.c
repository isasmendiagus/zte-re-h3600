// module: tm.ko
// function: cla_set_dn_multi_flow_cfg @ 0x12df4
// size: 396 bytes
//

undefined4 cla_set_dn_multi_flow_cfg(uint *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  if ((6 < g_tm_debug_level) &&
     (printk("[TM][cla_set_dn_multi_flow_cfg]input:\n"), 6 < g_tm_debug_level)) {
    printk("da_known = %d, gemport_valid = %d, gemport_id/default_uni_port = %d, tcontid_llid = %d, queue_id = %d, flow_id = %d\n"
           ,*param_1,param_1[1],param_1[2],param_1[3],param_1[4],param_1[5]);
  }
  if ((((param_1[1] < 2) && (param_1[3] < 0x28)) && (param_1[4] < 8)) &&
     ((param_1[5] < 0x200 && (*param_1 < 2)))) {
    uVar5 = param_1[2];
    if (param_1[1] == 0) {
      if (uVar5 < 0x20) goto LAB_00012e7c;
    }
    else if (uVar5 < 0x1000) {
LAB_00012e7c:
      iVar1 = tmOnuRegWrite(0x26,param_1[5] + param_1[4] * 0x200 + (param_1[3] & 0x1f) * 0x1000 +
                                 uVar5 * 0x20000,0,&claRegTable);
      iVar2 = tmOnuRegWrite(0x27,param_1[1],0,&claRegTable);
      iVar3 = tmOnuRegWrite(0x28,(param_1[3] << 0x1a) >> 0x1f,0,&claRegTable);
      iVar4 = tmOnuRegWrite(0x29,*param_1,0,&claRegTable);
      if (((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) {
        return 0;
      }
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][cla_set_dn_multi_flow_cfg]reg write failed\n");
      return 0xffffffff;
    }
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_set_dn_multi_flow_cfg]input invalid parameter!\n");
  }
  return 1;
}

