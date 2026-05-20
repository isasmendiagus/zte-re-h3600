// module: tm.ko
// function: pp_pm_get_flow_info @ 0x2d1d4
// size: 700 bytes
//

undefined4 pp_pm_get_flow_info(uint param_1,uint param_2,byte *param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  int local_38;
  undefined4 local_34 [4];
  
  local_34[0] = 0;
  local_34[1] = 0;
  local_34[2] = 0;
  local_38 = 0;
  if (g_tm_debug_level < 7) {
    bVar5 = param_1 != 0;
    if (param_1 < 2) {
      bVar5 = 0x3ff < param_2;
    }
    if (bVar5) {
LAB_0002d21c:
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_flow_info]input invalid parameter!\n");
      }
      return 1;
    }
LAB_0002d23c:
    uVar3 = 0;
    do {
      uVar3 = uVar3 + 1;
      pp_pm_ind_acc_done_get(&local_38);
      bVar5 = uVar3 == 0x13;
      if (uVar3 < 0x14) {
        bVar5 = local_38 == 0;
      }
    } while (bVar5);
    if (0x13 < uVar3) goto LAB_0002d268;
  }
  else {
    printk("[TM][pp_pm_get_flow_info]input:dir = %d, flow_ram_addr = %d\n",param_1,param_2);
    bVar5 = param_1 != 0;
    if (param_1 < 2) {
      bVar5 = 0x3ff < param_2;
    }
    if (bVar5) goto LAB_0002d21c;
    if (local_38 == 0) goto LAB_0002d23c;
  }
  uVar3 = pp_pm_set_indirect_cmd(1,0,param_2 | param_1 << 10);
  if (local_38 != 0) {
LAB_0002d2d4:
    iVar4 = 3;
    do {
      iVar4 = iVar4 + -1;
      uVar2 = pp_pm_ind_acc_data_get(iVar4,local_34 + iVar4);
      uVar3 = uVar3 | uVar2;
    } while (iVar4 != 0);
    if (uVar3 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_get_flow_info]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    *(undefined4 *)param_3 = local_34[0];
    uVar3 = g_tm_debug_level;
    *(undefined4 *)(param_3 + 4) = local_34[1];
    *(undefined4 *)(param_3 + 8) = local_34[2];
    if (6 < uVar3) {
      bVar1 = *param_3;
      uVar3 = ((uint)param_3[4] << 0x1d) >> 0x1f;
      printk("[TM][pp_pm_get_flow_info]output: dir = %d, flow_ram_addr = %d, sub_ram_index = %d, next_hop_idx = %d, dmac_en = %d, smac_en = %d, nat_dport = %d, nat_sport = %d, hl_ttl_en = %d\n"
             ,param_1,param_2,(param_3[8] & 0x1f) << 5 | (uint)(param_3[7] >> 3),
             (param_3[7] & 7) << 6 | (uint)(param_3[6] >> 2),bVar1 & 1,((uint)bVar1 << 0x1e) >> 0x1f
             ,(uint)param_3[1] << 6 | (uint)(bVar1 >> 2) | (param_3[2] & 3) << 0xe,
             (uint)param_3[3] << 6 | (uint)(param_3[2] >> 2) | (param_3[4] & 3) << 0xe,uVar3);
      if (6 < g_tm_debug_level) {
        uVar2 = (uint)param_3[4];
        printk(" tcp_udp_chk_en= %d, ip_chk_en = %d, dport_en = %d, sport_en = %d, dip_en = %d, sip_en = %d, subnet_id = %d, pri_dscp_tc_en = %d\n"
               ,(uVar2 << 0x1c) >> 0x1f,(uVar2 << 0x1b) >> 0x1f,(uVar2 << 0x1a) >> 0x1f,
               (uVar2 << 0x19) >> 0x1f,param_3[4] >> 7,param_3[5] & 1,
               ((uint)param_3[5] << 0x1b) >> 0x1c,((uint)param_3[6] << 0x1e) >> 0x1f,uVar3);
      }
    }
    return 0;
  }
  iVar4 = 0;
  do {
    iVar4 = iVar4 + 1;
    uVar2 = pp_pm_ind_acc_done_get(&local_38);
    uVar3 = uVar3 | uVar2;
    if (local_38 != 0) {
      if (iVar4 != 0x14) goto LAB_0002d2d4;
      break;
    }
  } while (iVar4 != 0x14);
LAB_0002d268:
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][pp_pm_get_flow_info]indirect access time out\n");
  return 0xffffffff;
}

