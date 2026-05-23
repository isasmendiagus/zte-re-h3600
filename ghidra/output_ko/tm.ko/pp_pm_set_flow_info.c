// module: tm.ko
// function: pp_pm_set_flow_info @ 0x2cfb8
// size: 540 bytes
//

undefined4 pp_pm_set_flow_info(uint param_1,uint param_2,byte *param_3)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  bool bVar7;
  int local_2c [2];
  
  local_2c[0] = 0;
  if (6 < g_tm_debug_level) {
    bVar1 = *param_3;
    uVar6 = ((uint)param_3[4] << 0x1d) >> 0x1f;
    printk("[TM][pp_pm_set_flow_info]input: dir = %d, flow_ram_addr = %d, sub_ram_index = %d, next_hop_idx = %d, dmac_en = %d, smac_en = %d, nat_dport = %d, nat_sport = %d, hl_ttl_en = %d\n"
           ,param_1,param_2,(param_3[8] & 0x1f) << 5 | (uint)(param_3[7] >> 3),
           (param_3[7] & 7) << 6 | (uint)(param_3[6] >> 2),bVar1 & 1,((uint)bVar1 << 0x1e) >> 0x1f,
           (uint)param_3[1] << 6 | (uint)(bVar1 >> 2) | (param_3[2] & 3) << 0xe,
           (uint)param_3[3] << 6 | (uint)(param_3[2] >> 2) | (param_3[4] & 3) << 0xe,uVar6);
    if (6 < g_tm_debug_level) {
      uVar4 = (uint)param_3[4];
      printk(" tcp_udp_chk_en= %d, ip_chk_en = %d, dport_en = %d, sport_en = %d, dip_en = %d, sip_en = %d, subnet_id = %d, pri_dscp_tc_en = %d\n"
             ,(uVar4 << 0x1c) >> 0x1f,(uVar4 << 0x1b) >> 0x1f,(uVar4 << 0x1a) >> 0x1f,
             (uVar4 << 0x19) >> 0x1f,param_3[4] >> 7,param_3[5] & 1,
             ((uint)param_3[5] << 0x1b) >> 0x1c,((uint)param_3[6] << 0x1e) >> 0x1f,uVar6);
    }
  }
  bVar7 = param_1 != 0;
  if (param_1 < 2) {
    bVar7 = 0x3ff < param_2;
  }
  if (bVar7) {
    if (g_tm_debug_level == 0) {
      uVar3 = 1;
    }
    else {
      printk("[TM][pp_pm_set_flow_info]input invalid parameter!\n");
      uVar3 = 1;
    }
  }
  else {
    uVar6 = 0;
    if (local_2c[0] == 0) {
      uVar4 = 0;
      uVar6 = 0;
      do {
        uVar4 = uVar4 + 1;
        uVar2 = pp_pm_ind_acc_done_get(local_2c);
        uVar6 = uVar6 | uVar2;
        bVar7 = uVar4 == 0x13;
        if (uVar4 < 0x14) {
          bVar7 = local_2c[0] == 0;
        }
      } while (bVar7);
      if (0x13 < uVar4) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][pp_pm_set_flow_info]indirect access time out\n");
        return 0xffffffff;
      }
    }
    param_3 = param_3 + 0xc;
    uVar4 = pp_pm_set_indirect_cmd(0,0,param_2 | param_1 << 10);
    iVar5 = 3;
    uVar4 = uVar4 | uVar6;
    do {
      iVar5 = iVar5 + -1;
      param_3 = param_3 + -4;
      uVar6 = pp_pm_ind_acc_data_set(iVar5,*(undefined4 *)param_3);
      uVar4 = uVar4 | uVar6;
    } while (iVar5 != 0);
    if (uVar4 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_set_flow_info]indirect access failed\n");
      }
      return 0xffffffff;
    }
    uVar3 = 0;
  }
  return uVar3;
}

