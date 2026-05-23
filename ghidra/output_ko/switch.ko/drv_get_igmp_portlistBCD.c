// module: switch.ko
// function: drv_get_igmp_portlistBCD @ 0x1b8f4
// size: 824 bytes
//

undefined4 drv_get_igmp_portlistBCD(int *param_1,int param_2,uint *param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint local_34;
  uint local_2c [2];
  
  local_2c[0] = 0;
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] input ERROR: sipnode=null\n");
    uVar3 = 0xffffffff;
  }
  else if (param_2 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] input ERROR: igmpentry=null\n");
    uVar3 = 0xffffffff;
  }
  else if (param_3 == (uint *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][drv_get_igmp_portlistBCD] input ERROR: portlist=null\n");
    uVar3 = 0xffffffff;
  }
  else {
    if ((((2 < g_switch_debug_level) &&
         (printk("[SW][drv_get_igmp_portlistBCD] input: portName=%s\n"), 2 < g_switch_debug_level))
        && (printk("[SW][drv_get_igmp_portlistBCD] input: dip=%3d.%3d.%3d.%3d\n",
                   *(undefined1 *)(param_2 + 0x17),*(undefined1 *)(param_2 + 0x16),
                   *(undefined1 *)(param_2 + 0x15),*(undefined1 *)(param_2 + 0x14)),
           2 < g_switch_debug_level)) &&
       ((printk("[SW][drv_get_igmp_portlistBCD] input: sip=%3d.%3d.%3d.%3d\n",
                *(undefined1 *)((int)param_1 + 3),*(undefined1 *)((int)param_1 + 2),
                *(undefined1 *)((int)param_1 + 1),(char)*param_1), 2 < g_switch_debug_level &&
        (printk("[SW][drv_get_igmp_portlistBCD] input: mode(1-in 2-EX)=%d\n",
                *(undefined4 *)(param_2 + 0x1c)), 2 < g_switch_debug_level)))) {
      printk("[SW][drv_get_igmp_portlistBCD] input: vlan=%d\n",*(undefined2 *)(param_2 + 0x10));
    }
    iVar5 = *(int *)(param_2 + 0x24);
    iVar7 = *param_1;
    if (iVar5 == 0) {
      if (2 < g_switch_debug_level) {
        printk("[SW][drv_get_igmp_portlistBCD] input: portInfo=null\n");
      }
      uVar4 = 0;
      local_34 = 0;
      uVar6 = uVar4;
    }
    else {
      uVar4 = 0;
      uVar6 = 0;
      local_34 = 0;
      do {
        iVar1 = get_sw_port_from_devname(iVar5,local_2c,1);
        if (iVar1 == -1) {
          if (g_switch_debug_level != 0) {
            printk("%s %d Error\n","drv_get_igmp_portlistBCD",0x78);
            return 0xffffffff;
          }
          return 0xffffffff;
        }
        local_2c[0] = 1 << (local_2c[0] & 0xff);
        if (2 < g_switch_debug_level) {
          printk("[SW][drv_get_igmp_portlistBCD] input: curPort=%d mode=%d\n",local_2c[0],
                 *(undefined4 *)(iVar5 + 0x14));
        }
        piVar2 = *(int **)(iVar5 + 0x10);
        if (piVar2 == (int *)0x0) {
          if (*(int *)(iVar5 + 0x14) == 2) {
            uVar4 = uVar4 | local_2c[0];
          }
        }
        else {
          do {
            if (*(int *)(param_2 + 0x1c) == 1) {
              if (*(int *)(iVar5 + 0x14) != 1) break;
              if (*piVar2 == iVar7) {
                local_34 = local_34 | local_2c[0];
                break;
              }
            }
            else {
              if ((*(int *)(param_2 + 0x1c) != 2) || (*(int *)(iVar5 + 0x14) != 2)) break;
              uVar4 = uVar4 | local_2c[0];
              if ((iVar7 != 0) &&
                 ((*piVar2 == iVar7 && (((DAT_0002c0e6 | DAT_0002c0e2) & local_2c[0]) == 0)))) {
                uVar6 = uVar6 | local_2c[0];
              }
            }
            piVar2 = (int *)piVar2[2];
          } while (piVar2 != (int *)0x0);
        }
        iVar5 = *(int *)(iVar5 + 0x1c);
        local_2c[0] = 0;
      } while (iVar5 != 0);
    }
    uVar3 = 0;
    param_3[1] = uVar6;
    *param_3 = local_34;
    param_3[2] = uVar4;
  }
  return uVar3;
}

