// module: switch.ko
// function: sw_reg_set_onu_swcap @ 0x13d9c
// size: 972 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sw_reg_set_onu_swcap(void)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined1 *puVar7;
  bool bVar8;
  byte local_2b;
  byte local_2a;
  byte local_29;
  int local_28;
  int local_24 [2];
  
  puVar4 = &g_sw_cap;
  uVar5 = 0;
  local_2b = 0;
  local_28 = 0;
  local_24[0] = 0;
  __memzero(&g_sw_cap,0x5c);
  __memzero(&local_2a,2);
  CspGetPortInfo(local_24);
  CspGetSwInfo(&local_28);
  if (local_28 == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)software_udf(0x12,0x140fc);
    (*pcVar1)();
  }
  iVar2 = *(int *)(local_28 + 8);
  if ((8 < iVar2) || (8 < *(ushort *)(local_24[0] + 2))) {
    if (g_switch_debug_level == 0) {
      return;
    }
    printk("[%s]:get eth cnt %d is larger than %d.\n","sw_reg_set_onu_swcap",iVar2,8);
    return;
  }
  _tm_port_unknwn_multicast_floodport_set = iVar2;
  if (iVar2 != 0) {
    puVar7 = (undefined1 *)0x2c0a7;
    iVar2 = local_28;
    do {
      iVar3 = iVar2 + uVar5 * 0xc;
      uVar6 = (uint)*(ushort *)(iVar3 + 0x12);
      puVar7 = puVar7 + 1;
      *puVar7 = (char)*(ushort *)(iVar3 + 0x12);
      zte_api_sw_vlan_get_port_inframemode[uVar6] = SUB41(uVar5,0);
      *(undefined2 *)((int)puVar4 + 0x1e) = *(undefined2 *)(iVar3 + 0x16);
      *(char *)(puVar4 + 7) = (char)*(undefined2 *)(iVar3 + 0x14);
      *(char *)((int)puVar4 + 0x1d) = (char)*(undefined2 *)(iVar3 + 0x10);
      if (*(uint *)(iVar2 + 4) != uVar5) {
        if (7 < uVar6) {
          printk("the switch port is error!!!\n");
          iVar2 = local_28;
        }
        _tm_tcont_que_sch_weight_get = _tm_tcont_que_sch_weight_get | 1 << (uVar6 & 0xff);
      }
      uVar5 = uVar5 + 1;
      puVar4 = puVar4 + 1;
    } while (uVar5 < *(uint *)(iVar2 + 8));
  }
  zte_api_sw_get_pon_port(&local_2b);
  ponPort = local_2b;
  if ((g_pon_work_mode & 0x10) == 0) {
    _tm_vlan_check_ena_set = 1 << (uint)local_2b;
    _zte_api_sw_mac_set_port_learnlimit = (uint)local_2b;
  }
  else {
    iVar2 = *(int *)(local_28 + 4);
    wanLogicPort = (undefined1)iVar2;
    if (iVar2 != -1) {
      local_2b = *(byte *)(iVar2 * 0xc + local_28 + 0x12);
      _tm_vlan_check_ena_set = 1 << (uint)local_2b;
      _zte_api_sw_mac_set_port_learnlimit = (uint)local_2b;
    }
  }
  if (*(short *)(local_24[0] + 8) == 0) {
    iVar2 = 0;
  }
  else {
    zte_api_sw_get_wlan_port(&local_2a);
    iVar2 = 2;
    DAT_0002c0e6 = (ushort)(1 << (uint)local_2a);
    _tm_broadcst_vltrans_table_print_get = (ushort)local_2a;
    DAT_0002c0ea = (ushort)(1 << (uint)local_29);
    _zte_api_pp_set_cpu_queue_rate = (ushort)local_29;
  }
  uVar6 = g_pon_work_mode;
  bVar8 = (g_pon_work_mode & 0x10) == 0;
  g_pon_work_mode = 1;
  _eth_type_trans =
       _tm_tcont_que_sch_weight_get | _tm_vlan_check_ena_set | (uint)DAT_0002c0e6 |
       (uint)DAT_0002c0ea;
  proc_create_data = _tm_port_unknwn_multicast_floodport_set + 1 + iVar2;
  uVar5 = (uint)bVar8;
  if ((bVar8) && ((uVar6 & 0x20) == 0)) {
    if ((uVar6 & 0x40) == 0) {
      if ((uVar6 & 0x100) == 0) {
        if ((uVar6 & 0x80) == 0) {
          if ((uVar6 & 0x200) == 0) {
            if ((uVar6 & 0x400) == 0) {
              if ((uVar6 & 0x800) == 0) {
                printk("config wan_type outof range! g_pon_work_mode = %d. \n");
                uVar5 = 0;
              }
              else {
                uVar5 = 7;
              }
            }
            else {
              uVar5 = 6;
            }
          }
          else {
            uVar5 = 5;
          }
        }
        else {
          uVar5 = 3;
        }
      }
      else {
        uVar5 = 2;
      }
    }
    else {
      uVar5 = 4;
    }
  }
  if ((g_pon_work_mode & 0x1a0) == 0) {
    if ((g_pon_work_mode & 0xe40) == 0) goto LAB_00014030;
    if (g_pon_work_mode == 1) {
      g_switch_debug_level = 3;
      goto LAB_00014030;
    }
    if (g_pon_work_mode != 0) goto LAB_00014030;
    uVar6 = 2;
  }
  else {
    uVar6 = g_pon_work_mode;
    if ((g_pon_work_mode != 1) && (g_pon_work_mode != 0)) goto LAB_00014030;
  }
  g_switch_debug_level = uVar6;
LAB_00014030:
  if ((g_pon_work_mode & 0x10) != 0) {
    g_switch_debug_level = 3;
    _eth_type_trans = _eth_type_trans | 1 << ponPort;
  }
  g_sw_cap = uVar5;
  printk("g_sw_cap.sw_uni_count=%d\n",_tm_port_unknwn_multicast_floodport_set);
  printk("g_sw_cap.sw_uni_mask=0x%x\n",_tm_tcont_que_sch_weight_get);
  printk("g_sw_cap.sw_wan_port=%d\n",_zte_api_sw_mac_set_port_learnlimit);
  printk("g_sw_cap.sw_wan_mask=0x%x\n",_tm_vlan_check_ena_set);
  printk("g_sw_cap.sw_all_port_count=%d\n",proc_create_data);
  printk("g_sw_cap.sw_all_port_mask=0x%x\n",_eth_type_trans);
  printk("g_sw_cap.gwtype%d\n",g_pon_work_mode);
  printk("g_sw_cap.wantype%d\n",g_sw_cap);
  printk("g_sw_cap.onutype%d\n",g_switch_debug_level);
  printk("ptSwInfo->wan_logicport=%d\n",*(undefined4 *)(local_28 + 4));
  return;
}

