// module: tm.ko
// function: pp_pm_get_external_flow_info @ 0x2d5e8
// size: 324 bytes
//

undefined4 pp_pm_get_external_flow_info(int param_1,int param_2,byte *param_3)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  if (param_1 == 0) {
    uVar2 = 0x1c00;
  }
  else {
    uVar2 = 0x9c00;
  }
  pbVar3 = (byte *)((param_2 + (uVar2 | 0xf140000)) * 0x10 + -1);
  pbVar6 = param_3 + 9;
  do {
    pbVar5 = pbVar6;
    pbVar3 = pbVar3 + 1;
    pbVar6 = pbVar5 + -1;
    *pbVar6 = *pbVar3;
  } while (pbVar6 != param_3);
  if (6 < g_tm_debug_level) {
    bVar1 = *pbVar6;
    uVar2 = ((uint)pbVar5[3] << 0x1d) >> 0x1f;
    printk("dir = %d, flow_ram_addr = %d, sub_ram_index = %d, next_hop_idx = %d, dmac_en = %d, smac_en = %d, nat_dport = %d, nat_sport = %d, hl_ttl_en = %d\n"
           ,param_1,param_2,(pbVar5[7] & 0x1f) << 5 | (uint)(pbVar5[6] >> 3),
           (pbVar5[6] & 7) << 6 | (uint)(pbVar5[5] >> 2),bVar1 & 1,((uint)bVar1 << 0x1e) >> 0x1f,
           (uint)*pbVar5 << 6 | (uint)(bVar1 >> 2) | (pbVar5[1] & 3) << 0xe,
           (uint)pbVar5[2] << 6 | (uint)(pbVar5[1] >> 2) | (pbVar5[3] & 3) << 0xe,uVar2);
    if (6 < g_tm_debug_level) {
      uVar4 = (uint)pbVar5[3];
      printk(" tcp_udp_chk_en= %d, ip_chk_en = %d, dport_en = %d, sport_en = %d, dip_en = %d, sip_en = %d, subnet_id = %d, pri_dscp_tc_en = %d\n"
             ,(uVar4 << 0x1c) >> 0x1f,(uVar4 << 0x1b) >> 0x1f,(uVar4 << 0x1a) >> 0x1f,
             (uVar4 << 0x19) >> 0x1f,pbVar5[3] >> 7,pbVar5[4] & 1,((uint)pbVar5[4] << 0x1b) >> 0x1c,
             ((uint)pbVar5[5] << 0x1e) >> 0x1f,uVar2);
    }
  }
  return 0;
}

