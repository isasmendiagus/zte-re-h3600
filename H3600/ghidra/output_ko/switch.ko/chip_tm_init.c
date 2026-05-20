// module: switch.ko
// function: chip_tm_init @ 0x136ac
// size: 1604 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void chip_tm_init(void)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  char *pcVar12;
  char *pcVar13;
  undefined4 uVar14;
  uint uVar15;
  code *pcVar16;
  undefined1 auStack_d6 [2];
  undefined4 local_d4;
  undefined4 local_d0;
  undefined1 local_cc;
  undefined1 local_cb;
  undefined1 local_ca;
  undefined4 local_c8;
  undefined1 local_c4;
  undefined1 local_c0 [4];
  undefined1 local_bc;
  undefined1 local_bb;
  undefined4 local_b8;
  undefined1 local_b0 [4];
  undefined1 local_ac;
  undefined1 local_ab;
  undefined1 local_aa;
  undefined4 local_a8;
  undefined1 local_a0;
  undefined1 local_9f;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_90;
  undefined1 local_88 [4];
  undefined1 local_84;
  undefined4 local_80;
  undefined1 local_7c;
  undefined4 local_78;
  undefined2 local_74;
  undefined4 local_70;
  uint local_6c [11];
  undefined1 local_40;
  undefined4 local_3c;
  undefined1 local_38;
  undefined1 local_37;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  
  local_d4 = 0;
  local_70 = 8000;
  local_d0 = 0;
  local_6c[0] = 0;
  local_6c[1] = 0;
  local_6c[2] = 0;
  local_6c[3] = 0;
  local_6c[4] = 0;
  local_6c[5] = 0;
  local_6c[6] = 0;
  __memzero(local_6c + 7,0x28);
  __memzero(&local_a0,0x18);
  __memzero(&local_cc,0xc);
  __memzero(auStack_d6,2);
  __memzero(local_c0,0x10);
  __memzero(local_88,0x18);
  __memzero(local_b0,0x10);
  if ((g_switch_debug_level & 0xfffffffd) == 1) {
    local_3c = 0;
    local_40 = 0;
    local_6c[10] = 0;
    local_6c[7] = 1;
  }
  else if (g_switch_debug_level == 0) {
    local_6c[7] = g_switch_debug_level;
    local_40 = 0;
    local_3c = 1;
    local_6c[10] = 1;
  }
  else if (g_switch_debug_level == 2) {
    local_3c = 0;
    local_6c[7] = 1;
    local_40 = 1;
    local_6c[10] = 1;
  }
  local_2e = 0x88a8;
  local_6c[8] = 0;
  local_6c[9] = 1;
  local_38 = 1;
  local_37 = 1;
  local_34 = 2000;
  local_32 = 0x8100;
  local_30 = 0x9100;
  local_2c = 0x9200;
  iVar2 = zte_api_sw_global_init(local_6c + 7);
  if (iVar2 != 0) {
    printk("zte_zx_api_sw_global_init failed!!!!\n");
  }
  if (_tm_set_p2pmode == 0) {
    uVar14 = 8000;
  }
  else {
    pcVar16 = zte_api_sw_mac_set_port_macfiltermode;
    uVar9 = 0;
    uVar15 = 0;
    do {
      if (uVar15 < _tm_port_unknwn_multicast_floodport_set) {
        uVar9 = (uint)(byte)*pcVar16;
      }
      else if ((uVar15 == _tm_port_unknwn_multicast_floodport_set) &&
              (_tm_broadcst_vltrans_table_print_get != 0)) {
        uVar9 = (uint)ponPort;
      }
      else if ((uVar15 == _tm_port_unknwn_multicast_floodport_set + 1) && (DAT_0002c0e2 != 0)) {
        uVar9 = (uint)(byte)zte_api_pp_set_cpu_queue_rate;
      }
      else if ((uVar15 == _tm_port_unknwn_multicast_floodport_set + 2) && (DAT_0002c0e6 != 0)) {
        uVar9 = (uint)(byte)eth_type_trans;
      }
      uVar1 = (undefined1)uVar9;
      local_cb = uVar9 != _tm_vlan_check_ena_set;
      local_c8 = 1;
      local_c4 = 1;
      local_cc = uVar1;
      local_ca = local_cb;
      uVar3 = zte_api_sw_port_init(&local_cc);
      uVar4 = zte_api_sw_vlan_set_port_pvid(uVar9,0,0);
      uVar5 = zte_api_sw_vlan_set_port_vlancfg(uVar9,0,0,3);
      uVar5 = uVar4 | uVar3 | uVar5;
      if ((g_switch_debug_level & 0xfffffffd) == 1) {
        uVar3 = zte_api_sw_vlan_set_port_vlancfg(uVar9,0,0xfff,3);
        uVar5 = uVar5 | uVar3;
      }
      else if ((g_switch_debug_level & 0xfffffffd) == 0) {
        uVar3 = zte_api_sw_vlan_set_port_vlancfg(uVar9,0,0,3);
        uVar5 = uVar5 | uVar3;
      }
      if (uVar9 == _tm_vlan_check_ena_set) {
        uVar3 = zte_api_sw_vlan_set_port_vlancfg(uVar9,0,0xfff,3);
        uVar5 = uVar5 | uVar3;
        if (wanLogicPort != -1) {
          uVar3 = zte_api_sw_vlan_set_port_vlancfg(ponPort,0,0xfff,3);
          uVar5 = uVar5 | uVar3;
        }
      }
      uVar3 = lan_up;
      if ((_zte_api_pp_set_cpu_queue_rate != uVar9) && (_eth_type_trans != uVar9)) {
        uVar3 = lan_up & ~(1 << uVar9);
      }
      iVar2 = zte_api_sw_port_set_port_isolatemask(uVar9,~uVar3);
      local_bc = 0;
      local_bb = 0;
      local_b8 = 0;
      local_c0[0] = uVar1;
      iVar6 = zte_api_sw_set_port_brdcast(local_c0);
      local_84 = 1;
      if ((g_switch_debug_level & 0xfffffffd) == 1) {
        if (ponPort == uVar9) {
LAB_000139c4:
          local_7c = 1;
        }
        else {
          local_7c = 0;
        }
      }
      else if ((g_switch_debug_level & 0xfffffffd) == 0) goto LAB_000139c4;
      local_80 = 1;
      local_78 = 0;
      local_74 = 0;
      local_88[0] = uVar1;
      iVar7 = zte_api_sw_set_port_unicast(local_88);
      local_ab = 0;
      local_aa = 0;
      local_ac = 1;
      if ((_zte_api_pp_set_cpu_queue_rate == uVar9) || (_eth_type_trans == uVar9)) {
        if ((g_switch_debug_level & 0xfffffffd) == 1) {
          local_a8 = 2;
        }
        else if ((g_switch_debug_level & 0xfffffffd) == 0) goto LAB_00013954;
      }
      else {
LAB_00013954:
        local_a8 = 0;
      }
      local_b0[0] = uVar1;
      iVar8 = zte_api_sw_set_port_muticast(local_b0);
      if ((((iVar2 != 0 || iVar6 != 0) || uVar5 != 0) || iVar7 != 0) || iVar8 != 0) {
        printk("zte_zx_api_sw_port_init fails!!!!\n");
      }
      uVar15 = uVar15 + 1;
      pcVar16 = pcVar16 + 1;
      uVar14 = local_70;
    } while (uVar15 < _tm_set_p2pmode);
  }
  local_9f = 1;
  if ((g_switch_debug_level & 0xfffffffd) == 1) {
    local_a0 = 0;
    local_9c = 1;
    local_98 = 1;
  }
  else if ((g_switch_debug_level & 0xfffffffd) == 0) {
    local_9c = 1;
    local_a0 = 1;
    local_98 = 2;
  }
  local_90 = 1;
  iVar2 = zte_api_pp_global_init(&local_a0);
  if (iVar2 != 0) {
    printk("zte_zx_api_pp_global_init  fails!!!!\n",uVar14);
  }
  puVar10 = &local_70;
  uVar9 = 0;
  while( true ) {
    uVar15 = uVar9 & 0xff;
    uVar9 = uVar9 + 1;
    iVar2 = zte_api_pp_set_cpu_queue_rate(uVar15,uVar14);
    if (uVar9 == 8) break;
    puVar10 = puVar10 + 1;
    uVar14 = *puVar10;
  }
  if (iVar2 != 0) {
    printk("zte_zx_api_pp_set_cpu_queue_rate  fails!!!!\n");
  }
  puVar10 = (undefined4 *)def_ptl_pkt_map_56600;
  do {
    uVar14 = *puVar10;
    puVar11 = puVar10 + 2;
    iVar2 = zte_api_pp_set_trap_queue(0,uVar14,*(undefined1 *)(puVar10 + 1));
    iVar6 = zte_api_pp_set_trap_queue(1,uVar14,*(undefined1 *)((int)puVar10 + 5));
    iVar7 = tm_protocol_pkt_limit_pps_set(0,5,1,8000);
    iVar8 = tm_protocol_pkt_limit_pps_set(1,5,1,8000);
    puVar10 = puVar11;
  } while (puVar11 != (undefined4 *)def_ptl_pkt_action_56605);
  if (((iVar7 != 0 || iVar8 != 0) || iVar6 != 0) || iVar2 != 0) {
    printk("zte_zx_api_pp_set_trap_queue  fails!!!!\n");
  }
  pcVar12 = def_ptl_pkt_action_56605;
  do {
    uVar14 = *(undefined4 *)pcVar12;
    pcVar13 = pcVar12 + 0xc;
    iVar2 = zte_api_pp_set_pro_action(0,uVar14,*(undefined4 *)(pcVar12 + 4));
    iVar6 = zte_api_pp_set_pro_action(1,uVar14,*(undefined4 *)(pcVar12 + 8));
    pcVar12 = pcVar13;
  } while (pcVar13 != "sw_reg_set_onu_swcap");
  if (iVar6 != 0 || iVar2 != 0) {
    printk("zte_zx_api_pp_set_pro_action  fails!!!!\n");
  }
  iVar2 = tm_cla_outspace_cfg_get(&local_d4,&local_d0);
  iVar6 = tm_cla_outspace_cfg_set(1,local_d0);
  if (iVar6 != 0 || iVar2 != 0) {
    printk("tm_cla_outspace_cfg_get/set fails!!!!\n");
  }
  printk("-------chip_tm_init end-----\n");
  return;
}

