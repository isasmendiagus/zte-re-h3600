// module: switch.ko
// function: drv_add_igmp_addr_gpon_sfu @ 0x1c790
// size: 2072 bytes
//

undefined4 drv_add_igmp_addr_gpon_sfu(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  uint local_64;
  int local_60;
  uint local_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 local_42;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  int local_34;
  
  local_64 = 0;
  local_60 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_add_igmp_addr] input ERROR: igmpEntry=null\n");
    return 0xffffffff;
  }
  iVar4 = tm_mac_ramaddr_sel_get(&local_60);
  if (iVar4 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_add_igmp_addr] FAIL: tm_mac_ramaddr_sel_get error\n");
    return 0xffffffff;
  }
  if (local_60 == 0 || local_60 == 3) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][tm_mac_ramaddr_sel_get] no ram for ipv4tabel FAIL\n");
    return 0xffffffff;
  }
  __memzero(&local_5c,0xc);
  __memzero(&local_50,0xc);
  __memzero(&local_44,0x1c);
  iVar4 = get_sw_port_from_devname(param_1,&local_64,1);
  if (iVar4 == -1) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("%s %d Error\n","drv_add_igmp_addr_gpon_sfu",0x238);
    return 0xffffffff;
  }
  local_64 = 1 << (local_64 & 0xff);
  if (g_switch_debug_level < 3) {
    puVar6 = *(uint **)(param_1 + 0x20);
    if (puVar6 != (uint *)0x0) {
LAB_0001c8d0:
      do {
        iVar5 = drv_get_igmp_portlistBCD(puVar6,param_1,&local_50);
        iVar3 = local_48;
        iVar2 = local_4c;
        iVar4 = local_50;
        if (iVar5 != 0) {
          if (g_switch_debug_level == 0) {
            return 0xffffffff;
          }
          printk("[SW][drv_get_igmp_portlistBCD] Fail!\n");
          return 0xffffffff;
        }
        if (g_switch_debug_level < 3) {
          if (*(int *)(param_1 + 0x1c) == 1) {
LAB_0001c9b4:
            if (iVar4 != 0) {
              __memzero(&local_44,0x1c);
              local_3c = *(uint *)(param_1 + 0x14);
              local_38 = (uint)*(ushort *)(param_1 + 0x10);
              local_44 = 1;
              local_40 = *puVar6;
              local_43 = 1;
              local_34 = iVar4;
              local_42 = 0;
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001cdfc:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: port_mask =%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                         local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
                           local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                       2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001cdfc;
                    }
                  }
                }
              }
              iVar4 = tm_ipv4table_add_set(&local_44);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_add_set]  portlist1 FAIL!!!\n");
                return 0xffffffff;
              }
            }
          }
          else {
            if (*puVar6 == 0) goto LAB_0001c8bc;
LAB_0001c918:
            if (iVar2 != 0) {
              __memzero(&local_44,0x1c);
              local_3c = *(uint *)(param_1 + 0x14);
              local_38 = (uint)*(ushort *)(param_1 + 0x10);
              local_44 = 1;
              local_40 = *puVar6;
              local_42 = 1;
              local_43 = 1;
              local_34 = iVar2;
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001cf88:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: port_mask =%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                         local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
                           local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                       2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001cf88;
                    }
                  }
                }
              }
              iVar4 = tm_ipv4table_add_set(&local_44);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_add_set] portlist2 FAIL!!!\n");
                return 0xffffffff;
              }
            }
            if (iVar3 != 0) {
              __memzero(&local_44,0x1c);
              local_3c = *(uint *)(param_1 + 0x14);
              uVar1 = *(ushort *)(param_1 + 0x10);
              local_40 = 0;
              goto joined_r0x0001ca74;
            }
          }
        }
        else {
          printk("[SW][drv_get_igmp_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n"
                 ,local_50,local_4c,local_48);
          if (*(int *)(param_1 + 0x1c) == 1) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_add_igmp_addr] IGMPv3 mode=IN\n");
            }
            goto LAB_0001c9b4;
          }
          if (*puVar6 != 0) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_add_igmp_addr] IGMPv3 mode=EX\n");
            }
            goto LAB_0001c918;
          }
          if (2 < g_switch_debug_level) {
            printk("[SW][drv_add_igmp_addr] IGMPv2 mode=EX\n");
          }
LAB_0001c8bc:
          if (iVar3 == 0) goto LAB_0001c8c4;
          __memzero(&local_44,0x1c);
          local_3c = *(uint *)(param_1 + 0x14);
          uVar1 = *(ushort *)(param_1 + 0x10);
          local_40 = *puVar6;
joined_r0x0001ca74:
          local_43 = 1;
          local_42 = 1;
          local_44 = 1;
          local_38 = (uint)uVar1;
          local_34 = iVar3;
          if (2 < g_switch_debug_level) {
            local_42 = 1;
            local_43 = 1;
            local_44 = 1;
            printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
            if (g_switch_debug_level < 3) {
LAB_0001cb14:
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: port_mask =%d\n",local_34);
              }
            }
            else {
              printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                     local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
                       local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                if ((2 < g_switch_debug_level) &&
                   (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                   2 < g_switch_debug_level)) {
                  printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
                  goto LAB_0001cb14;
                }
              }
            }
          }
          iVar4 = tm_ipv4table_add_set(&local_44);
          if (iVar4 != 0) goto LAB_0001c97c;
        }
LAB_0001c8c4:
        puVar6 = (uint *)puVar6[2];
        if (puVar6 == (uint *)0x0) {
          return 0;
        }
      } while( true );
    }
  }
  else {
    printk("[SW][drv_add_igmp_addr] input: dwPortListA=%d\n");
    puVar6 = *(uint **)(param_1 + 0x20);
    if (puVar6 != (uint *)0x0) goto LAB_0001c8d0;
    if (2 < g_switch_debug_level) {
      printk("[SW][drv_add_igmp_addr] IGMPv2 mode=EX\n");
    }
  }
  local_5c = 0;
  local_54 = 0;
  local_58 = 0;
  iVar4 = drv_get_igmp_portlistBCD(&local_5c,param_1,&local_50);
  if (iVar4 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] Fail!!!\n");
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][drv_get_igmp_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
           local_50,local_4c,local_48);
  }
  if (local_48 == 0) {
    return 0;
  }
  __memzero(&local_44,0x1c);
  local_3c = *(uint *)(param_1 + 0x14);
  local_38 = (uint)*(ushort *)(param_1 + 0x10);
  local_34 = local_48;
  local_40 = local_5c;
  local_44 = 1;
  local_42 = 1;
  local_43 = 1;
  if (g_switch_debug_level < 3) goto LAB_0001ccd4;
  printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,local_3c._2_1_,
           local_3c._1_1_,local_3c & 0xff);
    if (g_switch_debug_level < 3) goto LAB_0001ccd4;
    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,local_40._2_1_,
           local_40._1_1_,local_40 & 0xff);
    if ((g_switch_debug_level < 3) ||
       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
       g_switch_debug_level < 3)) goto LAB_0001ccd4;
    printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv4table_add_set] input: port_mask =%d\n",local_34);
  }
LAB_0001ccd4:
  iVar4 = tm_ipv4table_add_set(&local_44);
  if (iVar4 == 0) {
    return 0;
  }
LAB_0001c97c:
  if (g_switch_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[SW][tm_ipv4table_add_set] portlist3 FAIL!!!\n");
  return 0xffffffff;
}

