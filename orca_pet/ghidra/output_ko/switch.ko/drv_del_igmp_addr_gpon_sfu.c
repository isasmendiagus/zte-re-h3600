// module: switch.ko
// function: drv_del_igmp_addr_gpon_sfu @ 0x1d03c
// size: 2968 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 drv_del_igmp_addr_gpon_sfu(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  uint local_64;
  int local_60;
  uint local_5c [4];
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
    printk("[SW][drv_del_igmp_addr] input ERROR: igmpEntry=null\n");
    return 0xffffffff;
  }
  iVar3 = tm_mac_ramaddr_sel_get(&local_60);
  if (iVar3 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_igmp_addr] FAIL: tm_mac_ramaddr_sel_get error\n");
    return 0xffffffff;
  }
  if (local_60 == 0 || local_60 == 3) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_igmp_addr] Fail: no ram for ipv4tabel\n");
    return 0xffffffff;
  }
  __memzero(local_5c,0xc);
  __memzero(local_5c + 3,0xc);
  __memzero(&local_44,0x1c);
  iVar3 = get_sw_port_from_devname(param_1,&local_64,1);
  if (iVar3 == -1) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("%s %d Error\n","drv_del_igmp_addr_gpon_sfu",0x33c);
    return 0xffffffff;
  }
  local_64 = 1 << (local_64 & 0xff);
  if (g_switch_debug_level < 3) {
    puVar5 = *(uint **)(param_1 + 0x20);
    if (puVar5 != (uint *)0x0) {
LAB_0001d164:
      while (iVar4 = drv_get_igmp_portlistBCD(puVar5,param_1,local_5c + 3), iVar2 = local_48,
            iVar3 = local_4c, uVar1 = local_5c[3], iVar4 == 0) {
        if (g_switch_debug_level < 3) {
          if (*(int *)(param_1 + 0x1c) == 1) {
LAB_0001d314:
            __memzero(&local_44,0x1c);
            local_3c = *(uint *)(param_1 + 0x14);
            local_38 = (uint)*(ushort *)(param_1 + 0x10);
            local_44 = 1;
            local_40 = *puVar5;
            local_42 = 0;
            local_43 = 1;
            local_34 = uVar1;
            if (uVar1 == 0) {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_delete_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001da3c:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_delete_set] input: port_mask 1=%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_delete_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_
                         ,local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_delete_set] input: sip=%3d.%3d.%3d.%3d\n",
                           local_40._3_1_,local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_42)
                       , 2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_delete_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001da3c;
                    }
                  }
                }
              }
              iVar3 = tm_ipv4table_delete_set(&local_44);
              if (iVar3 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_delete_set] portlist1 FAIL!\n");
                return 0xffffffff;
              }
            }
            else {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001d8c4:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: port_mask 1=%d\n",local_34);
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
                      goto LAB_0001d8c4;
                    }
                  }
                }
              }
              iVar3 = tm_ipv4table_add_set(&local_44);
              if (iVar3 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_add_set] portlist1 FAIL!\n");
                return 0xffffffff;
              }
            }
          }
          else {
            if (*puVar5 == 0) goto LAB_0001d1ac;
LAB_0001d270:
            __memzero(&local_44,0x1c);
            local_3c = *(uint *)(param_1 + 0x14);
            local_38 = (uint)*(ushort *)(param_1 + 0x10);
            local_44 = 1;
            local_40 = *puVar5;
            local_42 = 1;
            local_43 = 1;
            local_34 = iVar3;
            if (iVar3 == 0) {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_delete_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001d808:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_delete_set] input: port_mask 2=%d\n",local_34);
                  }
                }
                else {
                  printk("[SW][tm_ipv4table_delete_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_
                         ,local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_delete_set] input: sip=%3d.%3d.%3d.%3d\n",
                           local_40._3_1_,local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                    if ((2 < g_switch_debug_level) &&
                       (printk("[SW][tm_ipv4table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_42)
                       , 2 < g_switch_debug_level)) {
                      printk("[SW][tm_ipv4table_delete_set] input: vlan_id=%d\n",local_38);
                      goto LAB_0001d808;
                    }
                  }
                }
              }
              iVar3 = tm_ipv4table_delete_set(&local_44);
              if (iVar3 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_delete_set portlist2] FAIL!\n");
                return 0xffffffff;
              }
            }
            else {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
                if (g_switch_debug_level < 3) {
LAB_0001daf8:
                  if (2 < g_switch_debug_level) {
                    printk("[SW][tm_ipv4table_add_set] input: port_mask 2=%d\n",local_34);
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
                      goto LAB_0001daf8;
                    }
                  }
                }
              }
              iVar3 = tm_ipv4table_add_set(&local_44);
              if (iVar3 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv4table_add_set] portlist2 FAIL!\n");
                return 0xffffffff;
              }
            }
          }
        }
        else {
          printk("[SW][drv_get_igmp_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n"
                 ,local_5c[3],local_4c,local_48);
          if (*(int *)(param_1 + 0x1c) == 1) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_del_igmp_addr] IGMPv3 mode=IN\n");
            }
            goto LAB_0001d314;
          }
          if (*puVar5 != 0) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_del_igmp_addr] IGMPv3 mode=EX\n");
            }
            goto LAB_0001d270;
          }
          if (2 < g_switch_debug_level) {
            printk("[SW][drv_del_igmp_addr] IGMPv2 mode=EX\n");
          }
LAB_0001d1ac:
          __memzero(&local_44,0x1c);
          local_3c = *(uint *)(param_1 + 0x14);
          local_38 = (uint)*(ushort *)(param_1 + 0x10);
          local_44 = 1;
          local_40 = *puVar5;
          local_42 = 1;
          local_43 = 1;
          local_34 = iVar2;
          if (iVar2 == 0) {
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv4table_delete_set] input: valid=%d\n");
              if (g_switch_debug_level < 3) {
LAB_0001d980:
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv4table_delete_set] input: port_mask 3=%d\n",local_34);
                }
              }
              else {
                printk("[SW][tm_ipv4table_delete_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
                       local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv4table_delete_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_
                         ,local_40._2_1_,local_40._1_1_,local_40 & 0xff);
                  if ((2 < g_switch_debug_level) &&
                     (printk("[SW][tm_ipv4table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_42),
                     2 < g_switch_debug_level)) {
                    printk("[SW][tm_ipv4table_delete_set] input: vlan_id=%d\n",local_38);
                    goto LAB_0001d980;
                  }
                }
              }
            }
            iVar3 = tm_ipv4table_delete_set(&local_44);
            if (iVar3 != 0) {
              if (g_switch_debug_level == 0) {
                return 0xffffffff;
              }
              printk("[SW][tm_ipv4table_delete_set] portlist3 FAIL!\n");
              return 0xffffffff;
            }
            goto LAB_0001d2ec;
          }
          if (2 < g_switch_debug_level) {
            printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
            if (g_switch_debug_level < 3) {
LAB_0001d74c:
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv4table_add_set] input: port_mask 3=%d\n",local_34);
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
                  goto LAB_0001d74c;
                }
              }
            }
          }
          iVar3 = tm_ipv4table_add_set(&local_44);
          if (iVar3 != 0) {
            if (g_switch_debug_level == 0) {
              return 0xffffffff;
            }
            printk("[SW][tm_ipv4table_add_set] portlist3 FAIL!\n");
            return 0xffffffff;
          }
        }
LAB_0001d2ec:
        puVar5 = (uint *)puVar5[2];
        if (puVar5 == (uint *)0x0) {
          return 0;
        }
      }
      goto LAB_0001d560;
    }
  }
  else {
    printk("[SW][drv_del_igmp_addr] input: dwPortListA=%d\n");
    puVar5 = *(uint **)(param_1 + 0x20);
    if (puVar5 != (uint *)0x0) goto LAB_0001d164;
    if (2 < g_switch_debug_level) {
      printk("[SW][drv_del_igmp_addr] IGMPv2 mode=EX\n");
    }
  }
  local_5c[0] = 0;
  local_5c[2] = 0;
  local_5c[1] = 0;
  iVar3 = drv_get_igmp_portlistBCD(local_5c,param_1,local_5c + 3);
  if (iVar3 != 0) {
LAB_0001d560:
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] FAIL!\n");
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][drv_get_igmp_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
           local_5c[3],local_4c,local_48);
  }
  __memzero(&local_44,0x1c);
  local_3c = *(uint *)(param_1 + 0x14);
  local_38 = (uint)*(ushort *)(param_1 + 0x10);
  local_34 = local_48;
  local_40 = local_5c[0];
  local_44 = 1;
  local_42 = 1;
  local_43 = 1;
  if (local_48 == 0) {
    if (g_switch_debug_level < 3) goto LAB_0001d584;
    printk("[SW][tm_ipv4table_delete_set] input: valid=%d\n");
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv4table_delete_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,
             local_3c._2_1_,local_3c._1_1_,local_3c & 0xff);
      if (g_switch_debug_level < 3) goto LAB_0001d584;
      printk("[SW][tm_ipv4table_delete_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,
             local_40._2_1_,local_40._1_1_,local_40 & 0xff);
      if ((g_switch_debug_level < 3) ||
         (printk("[SW][tm_ipv4table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_42),
         g_switch_debug_level < 3)) goto LAB_0001d584;
      printk("[SW][tm_ipv4table_delete_set] input: vlan_id=%d\n",local_38);
    }
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv4table_delete_set] input: port_mask 3=%d\n",local_34);
    }
LAB_0001d584:
    iVar3 = tm_ipv4table_delete_set(&local_44);
    if (iVar3 == 0) {
      return 0;
    }
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][tm_ipv4table_delete_set] portlist3 FAIL\n");
    return 0xffffffff;
  }
  if (g_switch_debug_level < 3) goto LAB_0001d530;
  printk("[SW][tm_ipv4table_add_set] input: valid=%d\n");
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv4table_add_set] input: dip=%3d.%3d.%3d.%3d\n",local_3c._3_1_,local_3c._2_1_,
           local_3c._1_1_,local_3c & 0xff);
    if (g_switch_debug_level < 3) goto LAB_0001d530;
    printk("[SW][tm_ipv4table_add_set] input: sip=%3d.%3d.%3d.%3d\n",local_40._3_1_,local_40._2_1_,
           local_40._1_1_,local_40 & 0xff);
    if ((g_switch_debug_level < 3) ||
       (printk("[SW][tm_ipv4table_add_set] input: mode(0-IN 1-EX)=%d\n",local_42),
       g_switch_debug_level < 3)) goto LAB_0001d530;
    printk("[SW][tm_ipv4table_add_set] input: vlan_id=%d\n",local_38);
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv4table_add_set] input: port_mask 3=%d\n",local_34);
  }
LAB_0001d530:
  iVar3 = tm_ipv4table_add_set(&local_44);
  if (iVar3 == 0) {
    return 0;
  }
  if (g_switch_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[SW][tm_ipv4table_add_set] portlist3 FAIL\n");
  return 0xffffffff;
}

