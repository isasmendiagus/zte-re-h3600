// module: tm.ko
// function: pp_pm_set_external_flow_info @ 0x2d490
// size: 344 bytes
//

undefined4 pp_pm_set_external_flow_info(int param_1,int param_2,byte *param_3)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  
  if ((6 < g_tm_debug_level) &&
     (bVar1 = param_3[6],
     printk("[TM][pp_pm_set_flow_info]input: dir = %d, flow_ram_addr = %d,           sub_ram_index = %d, next_hop_idx = %d, pri_dscp_tc_en = %d,flow_pri_en = %d, flow_pri = %d,subnet_id = %d,\n"
            ,param_1,param_2,(param_3[8] & 0x1f) << 5 | (uint)(param_3[7] >> 3),
            (param_3[7] & 7) << 6 | (uint)(bVar1 >> 2),((uint)bVar1 << 0x1e) >> 0x1f,bVar1 & 1,
            param_3[5] >> 5,((uint)param_3[5] << 0x1b) >> 0x1c), 6 < g_tm_debug_level)) {
    uVar3 = (uint)param_3[4];
    bVar1 = *param_3;
    printk(" sip_en = %d,dip_en = %d, sport_en = %d,dport_en = %d,         ip_chk_en = %d,tcp_udp_chk_en= %d,hl_ttl_en = %d,sport = %d,dport = %d,smac_en = %d,dmac_en = %d\n"
           ,param_3[5] & 1,param_3[4] >> 7,(uVar3 << 0x19) >> 0x1f,(uVar3 << 0x1a) >> 0x1f,
           (uVar3 << 0x1b) >> 0x1f,(uVar3 << 0x1c) >> 0x1f,(uVar3 << 0x1d) >> 0x1f,
           (uint)param_3[3] << 6 | (uint)(param_3[2] >> 2) | (uVar3 & 3) << 0xe,
           (uint)param_3[1] << 6 | (uint)(bVar1 >> 2) | (param_3[2] & 3) << 0xe,
           ((uint)bVar1 << 0x1e) >> 0x1f,bVar1 & 1);
  }
  if (param_1 == 0) {
    uVar3 = 0x1c00;
  }
  else {
    uVar3 = 0x9c00;
  }
  pbVar4 = param_3 + 9;
  pbVar2 = (byte *)((param_2 + (uVar3 | 0xf140000)) * 0x10 + -1);
  do {
    pbVar4 = pbVar4 + -1;
    pbVar2 = pbVar2 + 1;
    *pbVar2 = *pbVar4;
  } while (pbVar4 != param_3);
  return 0;
}

