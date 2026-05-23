// module: switch.ko
// function: sw_reg_set_onu_swcap @ 0x13cfc
// size: 956 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sw_reg_set_onu_swcap(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined1 *puVar6;
  bool bVar7;
  byte local_2b;
  byte local_2a;
  byte local_29;
  int local_28;
  int local_24 [2];
  
  uVar3 = 0;
  local_2b = 0;
  __memzero(&g_sw_cap,0x5c);
  __memzero(&local_2a,2);
  CspGetPortInfo(local_24);
  CspGetSwInfo(&local_28);
  iVar1 = *(int *)(local_28 + 8);
  if ((8 < iVar1) || (8 < *(ushort *)(local_24[0] + 2))) {
    if (g_switch_debug_level == 0) {
      return;
    }
    printk("[%s]:get eth cnt %d is larger than %d.\n","sw_reg_set_onu_swcap",iVar1,8);
    return;
  }
  _tm_port_unknwn_multicast_floodport_set = iVar1;
  if (iVar1 != 0) {
    puVar6 = (undefined1 *)0x2c0a3;
    iVar1 = local_28;
    puVar4 = &g_sw_cap;
    do {
      iVar2 = iVar1 + uVar3 * 0xc;
      uVar5 = (uint)*(ushort *)(iVar2 + 0x12);
      puVar6 = puVar6 + 1;
      *puVar6 = (char)*(ushort *)(iVar2 + 0x12);
      zte_api_sw_port_set_port_isolatemask[uVar5] = SUB41(uVar3,0);
      *(undefined2 *)((int)puVar4 + 0x1e) = *(undefined2 *)(iVar2 + 0x16);
      *(char *)(puVar4 + 7) = (char)*(undefined2 *)(iVar2 + 0x14);
      *(char *)((int)puVar4 + 0x1d) = (char)*(undefined2 *)(iVar2 + 0x10);
      bVar7 = *(uint *)(iVar1 + 4) != uVar3;
      uVar3 = uVar3 + 1;
      if (bVar7) {
        if (7 < uVar5) {
          printk("the switch port is error!!!\n");
          iVar1 = local_28;
        }
        _zte_api_sw_mac_set_port_learnlimit =
             _zte_api_sw_mac_set_port_learnlimit | 1 << (uVar5 & 0xff);
      }
      puVar4 = puVar4 + 1;
    } while (uVar3 < *(uint *)(iVar1 + 8));
  }
  zte_api_sw_get_pon_port(&local_2b);
  ponPort = local_2b;
  if ((g_pon_work_mode & 0x10) == 0) {
    _tm_broadcst_vltrans_table_print_get = 1 << (uint)local_2b;
    _tm_vlan_check_ena_set = (uint)local_2b;
  }
  else {
    iVar1 = *(int *)(local_28 + 4);
    wanLogicPort = (undefined1)iVar1;
    if (iVar1 != -1) {
      local_2b = *(byte *)(iVar1 * 0xc + local_28 + 0x12);
      _tm_broadcst_vltrans_table_print_get = 1 << (uint)local_2b;
      _tm_vlan_check_ena_set = (uint)local_2b;
    }
  }
  if (*(short *)(local_24[0] + 8) == 0) {
    iVar1 = 0;
  }
  else {
    zte_api_sw_get_wlan_port(&local_2a);
    iVar1 = 2;
    DAT_0002c0e2 = (ushort)(1 << (uint)local_2a);
    _zte_api_pp_set_cpu_queue_rate = (ushort)local_2a;
    DAT_0002c0e6 = (ushort)(1 << (uint)local_29);
    _eth_type_trans = (ushort)local_29;
  }
  uVar5 = g_pon_work_mode;
  bVar7 = (g_pon_work_mode & 0x10) == 0;
  g_pon_work_mode = 1;
  lan_up = _zte_api_sw_mac_set_port_learnlimit | _tm_broadcst_vltrans_table_print_get |
           (uint)DAT_0002c0e2 | (uint)DAT_0002c0e6;
  tm_set_p2pmode = _tm_port_unknwn_multicast_floodport_set + 1 + iVar1;
  uVar3 = (uint)bVar7;
  if ((bVar7) && ((uVar5 & 0x20) == 0)) {
    if ((uVar5 & 0x40) == 0) {
      if ((uVar5 & 0x100) == 0) {
        if ((uVar5 & 0x80) == 0) {
          if ((uVar5 & 0x200) == 0) {
            if ((uVar5 & 0x400) == 0) {
              if ((uVar5 & 0x800) == 0) {
                printk("config wan_type outof range! g_pon_work_mode = %d. \n");
                uVar3 = 0;
              }
              else {
                uVar3 = 7;
              }
            }
            else {
              uVar3 = 6;
            }
          }
          else {
            uVar3 = 5;
          }
        }
        else {
          uVar3 = 3;
        }
      }
      else {
        uVar3 = 2;
      }
    }
    else {
      uVar3 = 4;
    }
  }
  if ((g_pon_work_mode & 0x1a0) == 0) {
    if ((g_pon_work_mode & 0xe40) == 0) goto LAB_00013f80;
    if (g_pon_work_mode == 1) {
      g_switch_debug_level = 3;
      goto LAB_00013f80;
    }
    if (g_pon_work_mode != 0) goto LAB_00013f80;
    uVar5 = 2;
  }
  else {
    uVar5 = g_pon_work_mode;
    if ((g_pon_work_mode != 1) && (g_pon_work_mode != 0)) goto LAB_00013f80;
  }
  g_switch_debug_level = uVar5;
LAB_00013f80:
  if ((g_pon_work_mode & 0x10) != 0) {
    g_switch_debug_level = 3;
    lan_up = lan_up | 1 << ponPort;
  }
  g_sw_cap = uVar3;
  printk("g_sw_cap.sw_uni_count=%d\n",_tm_port_unknwn_multicast_floodport_set);
  printk("g_sw_cap.sw_uni_mask=0x%x\n",_zte_api_sw_mac_set_port_learnlimit);
  printk("g_sw_cap.sw_wan_port=%d\n",_tm_vlan_check_ena_set);
  printk("g_sw_cap.sw_wan_mask=0x%x\n",_tm_broadcst_vltrans_table_print_get);
  printk("g_sw_cap.sw_all_port_count=%d\n",tm_set_p2pmode);
  printk("g_sw_cap.sw_all_port_mask=0x%x\n",lan_up);
  printk("g_sw_cap.gwtype%d\n",g_pon_work_mode);
  printk("g_sw_cap.wantype%d\n",g_sw_cap);
  printk("g_sw_cap.onutype%d\n",g_switch_debug_level);
  printk("ptSwInfo->wan_logicport=%d\n",*(undefined4 *)(local_28 + 4));
  return;
}

