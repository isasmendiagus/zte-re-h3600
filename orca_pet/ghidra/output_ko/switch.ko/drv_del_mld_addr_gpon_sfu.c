// module: switch.ko
// function: drv_del_mld_addr_gpon_sfu @ 0x1e5cc
// size: 3708 bytes
//

undefined4 drv_del_mld_addr_gpon_sfu(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  int *piVar7;
  undefined2 *puVar8;
  int *piVar9;
  undefined2 *puVar10;
  void *__s1;
  uint local_98;
  uint local_94;
  int local_90;
  int local_8c;
  int local_88;
  undefined1 auStack_84 [16];
  undefined1 auStack_74 [16];
  undefined4 local_64;
  undefined4 local_60;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  uint local_58;
  undefined4 local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  undefined2 local_48;
  undefined2 local_46;
  int local_44;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 auStack_30 [6];
  
  local_98 = 0;
  local_94 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_mld_addr] input ERROR: mldEntry=null\n");
    return 0xffffffff;
  }
  iVar4 = tm_mac_ramaddr_sel_get(&local_94);
  if (iVar4 != 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_mld_addr] FAIL: tm_mac_ramaddr_sel_get error\n");
    return 0xffffffff;
  }
  if ((local_94 & 0xfffffffd) == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_del_mld_addr] Fail: no ram for ipv6tabel\n");
    return 0xffffffff;
  }
  __memzero(auStack_74,0x18);
  __memzero(&local_90,0xc);
  __memzero(&local_5c,0x34);
  __memzero(auStack_84,0x10);
  iVar4 = get_sw_port_from_devname(param_1,&local_98,1);
  if (iVar4 == -1) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("%s %d Error\n","drv_del_mld_addr_gpon_sfu",0x5b4);
    return 0xffffffff;
  }
  local_98 = 1 << (local_98 & 0xff);
  if (g_switch_debug_level < 3) {
    __s1 = *(void **)(param_1 + 0x28);
    if (__s1 != (void *)0x0) {
LAB_0001e6fc:
      while (iVar5 = drv_get_mld_portlistBCD(__s1,param_1,&local_90), iVar3 = local_88,
            iVar2 = local_8c, iVar4 = local_90, iVar5 == 0) {
        if (g_switch_debug_level < 3) {
          if (*(int *)(param_1 + 0x24) == 1) {
LAB_0001e918:
            __memzero(&local_5c,0x34);
            puVar6 = (undefined1 *)(param_1 + 0x22);
            local_5c = 1;
            piVar7 = &local_54;
            do {
              puVar6 = puVar6 + -1;
              piVar9 = (int *)((int)piVar7 + 1);
              *(undefined1 *)piVar7 = *puVar6;
              piVar7 = piVar9;
            } while (piVar9 != &local_44);
            puVar6 = (undefined1 *)((int)__s1 + 0x10);
            puVar8 = &local_40;
            do {
              puVar6 = puVar6 + -1;
              puVar10 = (undefined2 *)((int)puVar8 + 1);
              *(undefined1 *)puVar8 = *puVar6;
              puVar8 = puVar10;
            } while (puVar10 != auStack_30);
            local_58 = (uint)*(ushort *)(param_1 + 0x10);
            local_5b = 1;
            local_44 = iVar4;
            local_5a = 0;
            if (iVar4 == 0) {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_delete_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001ea6c;
                  printk("[SW][tm_ipv6table_delete_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_delete_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001ea6c:
              iVar4 = tm_ipv6table_delete_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_delete_set] portlist1 FAIL!\n");
                return 0xffffffff;
              }
            }
            else {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001e994;
                  printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001e994:
              iVar4 = tm_ipv6table_add_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_add_set] portlist1 FAIL!\n");
                return 0xffffffff;
              }
            }
          }
          else {
            iVar4 = memcmp(__s1,auStack_84,0x10);
            if (iVar4 != 0) goto LAB_0001e848;
LAB_0001e750:
            __memzero(&local_5c,0x34);
            puVar6 = (undefined1 *)(param_1 + 0x22);
            local_5c = 1;
            piVar7 = &local_54;
            do {
              puVar6 = puVar6 + -1;
              piVar9 = (int *)((int)piVar7 + 1);
              *(undefined1 *)piVar7 = *puVar6;
              piVar7 = piVar9;
            } while (piVar9 != &local_44);
            puVar8 = &local_40;
            do {
              puVar10 = (undefined2 *)((int)puVar8 + 1);
              *(undefined1 *)puVar8 = 0;
              puVar8 = puVar10;
            } while (puVar10 != auStack_30);
            local_58 = (uint)*(ushort *)(param_1 + 0x10);
            local_44 = iVar3;
            local_5a = 1;
            local_5b = 1;
            if (iVar3 == 0) {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_delete_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001ea34;
                  printk("[SW][tm_ipv6table_delete_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_delete_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001ea34:
              iVar4 = tm_ipv6table_delete_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_delete_set] portlist3 FAIL!\n");
                return 0xffffffff;
              }
            }
            else {
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                         local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                         (undefined2)local_54);
                  if (((g_switch_debug_level < 3) ||
                      (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                              ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,
                              local_40), g_switch_debug_level < 3)) ||
                     (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                     g_switch_debug_level < 3)) goto LAB_0001e7c4;
                  printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
                }
                if (2 < g_switch_debug_level) {
                  printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
                }
              }
LAB_0001e7c4:
              iVar4 = tm_ipv6table_add_set(&local_5c);
              if (iVar4 != 0) {
                if (g_switch_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[SW][tm_ipv6table_add_set] portlist3 FAIL!\n");
                return 0xffffffff;
              }
            }
          }
        }
        else {
          printk("[SW][drv_get_mld_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
                 local_90,local_8c,local_88);
          uVar1 = g_switch_debug_level;
          if (*(int *)(param_1 + 0x24) == 1) {
            if (2 < g_switch_debug_level) {
              printk("[SW][drv_del_mld_addr] MLDv2 mode=IN\n");
            }
            goto LAB_0001e918;
          }
          iVar4 = memcmp(__s1,auStack_84,0x10);
          if (iVar4 == 0) {
            if (2 < uVar1) {
              printk("[SW][drv_del_mld_addr] MLDv1 mode=EX\n");
            }
            goto LAB_0001e750;
          }
          if (2 < uVar1) {
            printk("[SW][drv_del_mld_addr] MLDv2 mode=EX\n");
          }
LAB_0001e848:
          __memzero(&local_5c,0x34);
          puVar6 = (undefined1 *)(param_1 + 0x22);
          local_5c = 1;
          piVar7 = &local_54;
          do {
            puVar6 = puVar6 + -1;
            piVar9 = (int *)((int)piVar7 + 1);
            *(undefined1 *)piVar7 = *puVar6;
            piVar7 = piVar9;
          } while (piVar9 != &local_44);
          puVar6 = (undefined1 *)((int)__s1 + 0x10);
          puVar8 = &local_40;
          do {
            puVar6 = puVar6 + -1;
            puVar10 = (undefined2 *)((int)puVar8 + 1);
            *(undefined1 *)puVar8 = *puVar6;
            puVar8 = puVar10;
          } while (puVar10 != auStack_30);
          local_58 = (uint)*(ushort *)(param_1 + 0x10);
          local_44 = iVar2;
          local_5a = 1;
          local_5b = 1;
          if (iVar2 == 0) {
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv6table_delete_set] input: valid=%d\n",1);
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                       local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                       (undefined2)local_54);
                if (((g_switch_debug_level < 3) ||
                    (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n"
                            ,local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40
                           ), g_switch_debug_level < 3)) ||
                   (printk("[SW][tm_ipv6table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                   g_switch_debug_level < 3)) goto LAB_0001e9fc;
                printk("[SW][tm_ipv6table_delete_set] input: vlan_id=%d\n",local_58);
              }
              if (2 < g_switch_debug_level) {
                printk("[SW][tm_ipv6table_delete_set] input: port_mask 1=%d\n",local_44);
              }
            }
LAB_0001e9fc:
            iVar4 = tm_ipv6table_delete_set(&local_5c);
            if (iVar4 != 0) {
              if (g_switch_debug_level == 0) {
                return 0xffffffff;
              }
              printk("[SW][tm_ipv6table_delete_set portlist2] FAIL!\n");
              return 0xffffffff;
            }
            goto LAB_0001e8f0;
          }
          if (2 < g_switch_debug_level) {
            printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                     local_46,local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,
                     (undefined2)local_54);
              if (((g_switch_debug_level < 3) ||
                  (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                          local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40),
                  g_switch_debug_level < 3)) ||
                 (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
                 g_switch_debug_level < 3)) goto LAB_0001e8c0;
              printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
            }
            if (2 < g_switch_debug_level) {
              printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
            }
          }
LAB_0001e8c0:
          iVar4 = tm_ipv6table_add_set(&local_5c);
          if (iVar4 != 0) {
            if (g_switch_debug_level == 0) {
              return 0xffffffff;
            }
            printk("[SW][tm_ipv6table_add_set] portlist2 FAIL!\n");
            return 0xffffffff;
          }
        }
LAB_0001e8f0:
        __s1 = *(void **)((int)__s1 + 0x14);
        if (__s1 == (void *)0x0) {
          return 0;
        }
      }
      goto LAB_0001ebb4;
    }
  }
  else {
    printk("[SW][drv_del_mld_addr] input: dwPortListA=%d\n");
    __s1 = *(void **)(param_1 + 0x28);
    if (__s1 != (void *)0x0) goto LAB_0001e6fc;
    if (2 < g_switch_debug_level) {
      printk("[SW][drv_del_mld_addr] MLDv1 mode=EX\n");
    }
  }
  local_60 = 0;
  local_64 = 0;
  iVar4 = drv_get_mld_portlistBCD(auStack_74,param_1,&local_90);
  if (iVar4 != 0) {
LAB_0001ebb4:
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_mld_portlistBCD] FAIL!\n");
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][drv_get_mld_portlistBCD] output: portlistB=%d, portlistC=%d, portlistD=%d\n",
           local_90,local_8c,local_88);
  }
  __memzero(&local_5c,0x34);
  puVar6 = (undefined1 *)(param_1 + 0x22);
  local_5c = 1;
  piVar7 = &local_54;
  do {
    puVar6 = puVar6 + -1;
    piVar9 = (int *)((int)piVar7 + 1);
    *(undefined1 *)piVar7 = *puVar6;
    piVar7 = piVar9;
  } while (piVar9 != &local_44);
  puVar8 = &local_40;
  do {
    puVar10 = (undefined2 *)((int)puVar8 + 1);
    *(undefined1 *)puVar8 = 0;
    puVar8 = puVar10;
  } while (puVar10 != auStack_30);
  local_58 = (uint)*(ushort *)(param_1 + 0x10);
  local_44 = local_88;
  local_5a = 1;
  local_5b = 1;
  if (local_88 == 0) {
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv6table_delete_set] input: valid=%d\n",1);
      if (2 < g_switch_debug_level) {
        printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",local_46,
               local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,(undefined2)local_54);
        if (((g_switch_debug_level < 3) ||
            (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",
                    local_32,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40),
            g_switch_debug_level < 3)) ||
           (printk("[SW][tm_ipv6table_delete_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
           g_switch_debug_level < 3)) goto LAB_0001ebd8;
        printk("[SW][tm_ipv6table_delete_set] input: vlan_id=%d\n",local_58);
      }
      if (2 < g_switch_debug_level) {
        printk("[SW][tm_ipv6table_delete_set] input: port_mask 1=%d\n",local_44);
      }
    }
LAB_0001ebd8:
    iVar4 = tm_ipv6table_delete_set(&local_5c);
    if (iVar4 == 0) {
      return 0;
    }
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][tm_ipv6table_delete_set] portlist3 FAIL\n");
    return 0xffffffff;
  }
  if (2 < g_switch_debug_level) {
    printk("[SW][tm_ipv6table_add_set] input: valid=%d\n",1);
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv6table_add_set] input: dip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",local_46,
             local_48,local_4a,local_4c,local_4e,local_50,local_54._2_2_,(undefined2)local_54);
      if (((g_switch_debug_level < 3) ||
          (printk("[SW][tm_ipv6table_add_set] input: sip=%4x:%4x:%4x:%4x:%4x:%4x:%4x:%4x\n",local_32
                  ,local_34,local_36,local_38,local_3a,local_3c,local_3e,local_40),
          g_switch_debug_level < 3)) ||
         (printk("[SW][tm_ipv6table_add_set] input: mode(0-IN 1-EX)=%d\n",local_5a),
         g_switch_debug_level < 3)) goto LAB_0001eb84;
      printk("[SW][tm_ipv6table_add_set] input: vlan_id=%d\n",local_58);
    }
    if (2 < g_switch_debug_level) {
      printk("[SW][tm_ipv6table_add_set] input: port_mask 1=%d\n",local_44);
    }
  }
LAB_0001eb84:
  iVar4 = tm_ipv6table_add_set(&local_5c);
  if (iVar4 == 0) {
    return 0;
  }
  if (g_switch_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[SW][tm_ipv6table_add_set] portlist3 FAIL\n");
  return 0xffffffff;
}

