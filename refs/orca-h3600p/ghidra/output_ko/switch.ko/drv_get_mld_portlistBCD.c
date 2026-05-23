// module: switch.ko
// function: drv_get_mld_portlistBCD @ 0x1bcbc
// size: 1080 bytes
//

undefined4 drv_get_mld_portlistBCD(undefined4 *param_1,int param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  void *__s1;
  uint local_54;
  uint local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined1 auStack_38 [20];
  
  local_4c = 0;
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar5 = 0xffffffff;
    printk("[SW][drv_get_mld_portlistBCD] input ERROR: sipnode=null\n");
  }
  else if (param_2 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar5 = 0xffffffff;
    printk("[SW][drv_get_mld_portlistBCD] input ERROR: mldEntry=null\n");
  }
  else if (param_3 == (uint *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar5 = 0xffffffff;
    printk("[SW][drv_get_mld_portlistBCD] input ERROR: portlist=null\n");
  }
  else {
    if ((((2 < g_switch_debug_level) &&
         (printk("[SW][drv_get_mld_portlistBCD] input: portname=%s\n"), 2 < g_switch_debug_level))
        && (printk("[SW][drv_get_mld_portlistBCD] input: dip=%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x\n"
                   ,*(undefined1 *)(param_2 + 0x12),*(undefined1 *)(param_2 + 0x13),
                   *(undefined1 *)(param_2 + 0x14),*(undefined1 *)(param_2 + 0x15),
                   *(undefined1 *)(param_2 + 0x16),*(undefined1 *)(param_2 + 0x17),
                   *(undefined1 *)(param_2 + 0x18),*(undefined1 *)(param_2 + 0x19),
                   *(undefined1 *)(param_2 + 0x1a),*(undefined1 *)(param_2 + 0x1b),
                   *(undefined1 *)(param_2 + 0x1c),*(undefined1 *)(param_2 + 0x1d),
                   *(undefined1 *)(param_2 + 0x1e),*(undefined1 *)(param_2 + 0x1f),
                   *(undefined1 *)(param_2 + 0x20),*(undefined1 *)(param_2 + 0x21)),
           2 < g_switch_debug_level)) &&
       ((printk("[SW][drv_get_mld_portlistBCD] input: sip=%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x:%2x%2x\n"
                ,*(undefined1 *)param_1,*(undefined1 *)((int)param_1 + 1),
                *(undefined1 *)((int)param_1 + 2),*(undefined1 *)((int)param_1 + 3),
                *(undefined1 *)(param_1 + 1),*(undefined1 *)((int)param_1 + 5),
                *(undefined1 *)((int)param_1 + 6),*(undefined1 *)((int)param_1 + 7),
                *(undefined1 *)(param_1 + 2),*(undefined1 *)((int)param_1 + 9),
                *(undefined1 *)((int)param_1 + 10),*(undefined1 *)((int)param_1 + 0xb),
                *(undefined1 *)(param_1 + 3),*(undefined1 *)((int)param_1 + 0xd),
                *(undefined1 *)((int)param_1 + 0xe),*(undefined1 *)((int)param_1 + 0xf)),
        2 < g_switch_debug_level &&
        (printk("[SW][drv_get_mld_portlistBCD] input: mode(1-in 2-EX)=%d\n",
                *(undefined4 *)(param_2 + 0x24)), 2 < g_switch_debug_level)))) {
      printk("[SW][drv_get_mld_portlistBCD] input: vlan=%d\n",*(undefined2 *)(param_2 + 0x10));
    }
    __memzero(&local_48,0x10);
    __memzero(auStack_38,0x10);
    local_48 = *param_1;
    uStack_44 = param_1[1];
    uStack_40 = param_1[2];
    iVar6 = *(int *)(param_2 + 0x2c);
    uStack_3c = param_1[3];
    if (iVar6 == 0) {
      if (2 < g_switch_debug_level) {
        printk("[SW][drv_get_mld_portlistBCD] input: portInfo=null\n");
      }
      uVar4 = 0;
      local_54 = 0;
      uVar8 = uVar4;
    }
    else {
      uVar4 = 0;
      uVar8 = 0;
      local_54 = 0;
      do {
        iVar2 = get_sw_port_from_devname(iVar6,&local_4c,1);
        if (iVar2 == -1) {
          if (g_switch_debug_level != 0) {
            printk("%s %d Error\n","drv_get_mld_portlistBCD",0xe8);
            return 0xffffffff;
          }
          return 0xffffffff;
        }
        local_4c = 1 << (local_4c & 0xff);
        if (2 < g_switch_debug_level) {
          printk("[SW][drv_get_mld_portlistBCD] input: curPort=%d mode=%d\n",local_4c,
                 *(undefined4 *)(iVar6 + 0x14));
        }
        uVar1 = local_4c;
        __s1 = *(void **)(iVar6 + 0x10);
        if (__s1 == (void *)0x0) {
          if (*(int *)(iVar6 + 0x14) == 2) {
            uVar4 = uVar4 | local_4c;
          }
        }
        else {
          uVar7 = (DAT_0002c0ea | DAT_0002c0e6) & local_4c;
          iVar2 = *(int *)(param_2 + 0x24);
          do {
            if (iVar2 == 1) {
              if (*(int *)(iVar6 + 0x14) != 1) break;
              iVar3 = memcmp(__s1,&local_48,0x10);
              if (iVar3 == 0) {
                local_54 = local_54 | uVar1;
                break;
              }
            }
            else {
              if ((iVar2 != 2) || (*(int *)(iVar6 + 0x14) != 2)) break;
              iVar3 = memcmp(auStack_38,&local_48,0x10);
              uVar4 = uVar4 | uVar1;
              if ((iVar3 != 0) &&
                 ((iVar3 = memcmp(__s1,&local_48,0x10), iVar3 == 0 && (uVar7 == 0)))) {
                uVar8 = uVar8 | uVar1;
              }
            }
            __s1 = *(void **)((int)__s1 + 0x14);
          } while (__s1 != (void *)0x0);
        }
        iVar6 = *(int *)(iVar6 + 0x1c);
        local_4c = 0;
      } while (iVar6 != 0);
    }
    uVar5 = 0;
    param_3[1] = uVar8;
    *param_3 = local_54;
    param_3[2] = uVar4;
  }
  return uVar5;
}

