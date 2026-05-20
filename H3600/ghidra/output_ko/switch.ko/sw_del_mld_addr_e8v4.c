// module: switch.ko
// function: sw_del_mld_addr_e8v4 @ 0x2009c
// size: 524 bytes
//

undefined4 sw_del_mld_addr_e8v4(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  uint local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  uint local_50;
  uint auStack_4c [4];
  uint local_3c [7];
  
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&local_64,0x10);
    local_64 = *param_1;
    local_60 = param_1[1];
    local_5c = param_1[2];
    local_58 = param_1[3];
    if (2 < g_switch_debug_level) {
      printk("sw_del_mld_addr_e8v4 portname %s\n",&local_64);
    }
    iVar2 = get_sw_port_from_devname(&local_64,&local_68,1);
    if (iVar2 == 0) {
      uVar1 = 1 << (local_68 & 0xff);
      __memzero(&local_54,0x34);
      uVar6 = *(ushort *)(param_1 + 4) & 0xfff;
      if (2 < g_switch_debug_level) {
        printk("sw_add_mld_addr_e8v4 dip:");
      }
      puVar3 = (undefined1 *)((int)param_1 + 0x22);
      puVar4 = auStack_4c;
      uVar7 = g_switch_debug_level;
      do {
        puVar3 = puVar3 + -1;
        puVar5 = (uint *)((int)puVar4 + 1);
        *(undefined1 *)puVar4 = *puVar3;
        if (2 < uVar7) {
          printk("%2.2x.\n");
          uVar7 = g_switch_debug_level;
        }
        puVar4 = puVar5;
      } while (puVar5 != local_3c);
      if (2 < uVar7) {
        printk("\nsw_add_mld_addr_e8v4 portMsk 0x%8.8x, vlan %d\n",uVar1,uVar6);
      }
      local_50 = uVar6;
      if (uVar1 == 0) {
        tm_ipv6table_delete_set(&local_54);
        sw_mld_mulrule_deal(auStack_4c,uVar6,0);
        return 0;
      }
      iVar2 = tm_ipv6table_lookup_get();
      if (iVar2 == 0) {
        if (uVar1 != local_3c[0]) {
          local_3c[0] = local_3c[0] & ~uVar1;
          local_53 = 0;
          local_54 = 1;
          local_52 = 1;
          tm_ipv6table_add_set();
          return 0;
        }
        tm_ipv6table_delete_set(&local_54);
        sw_mld_mulrule_deal(auStack_4c,uVar6,0);
        return 0;
      }
      if (g_switch_debug_level != 0) {
        printk("tm_ipv6table_lookup_get ERROR: vlan_id=%d\n",local_50);
        return 0xffffffff;
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("get_sw_port_from_devname curPort ERROR: portname=%s\n",&local_64);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

