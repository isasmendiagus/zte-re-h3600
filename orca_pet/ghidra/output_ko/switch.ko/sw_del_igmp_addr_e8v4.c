// module: switch.ko
// function: sw_del_igmp_addr_e8v4 @ 0x1fbe4
// size: 556 bytes
//

undefined4 sw_del_igmp_addr_e8v4(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  uint local_2c;
  
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  if (2 < g_switch_debug_level) {
    printk("sw_del_igmp_addr_e8v411\n");
  }
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&local_4c,0x10);
    local_4c = *param_1;
    local_48 = param_1[1];
    local_44 = param_1[2];
    local_40 = param_1[3];
    if (2 < g_switch_debug_level) {
      printk("sw_del_igmp_addr_e8v4 portname %s\n",&local_4c);
    }
    iVar2 = get_sw_port_from_devname(&local_4c,&local_50,1);
    if (iVar2 == 0) {
      uVar4 = param_1[5];
      uVar1 = 1 << (local_50 & 0xff);
      uVar3 = *(ushort *)(param_1 + 4) & 0xfff;
      if (2 < g_switch_debug_level) {
        printk("sw_del_igmp_addr_e8v4 portMsk 0x%8.8x, sip 0x%8.8x, dip 0x%8.8x, vlan %d\n",uVar1,0,
               uVar4,uVar3);
      }
      __memzero(&local_3c);
      local_38 = 0;
      local_3a = 1;
      local_34 = uVar4;
      local_30 = uVar3;
      if (uVar1 == 0) {
        tm_ipv4table_delete_set(&local_3c);
        sw_igmp_mulrule_deal(uVar4,uVar3,0);
        return 0;
      }
      iVar2 = tm_ipv4table_lookup_get();
      if (iVar2 == 0) {
        if (uVar1 != local_2c) {
          local_2c = local_2c & ~uVar1;
          local_3c = 1;
          local_3a = 1;
          local_3b = 0;
          if (2 < g_switch_debug_level) {
            printk("sw_del_igmp_addr_e8v4 2 portmask %d\n");
          }
          tm_ipv4table_add_set(&local_3c);
          return 0;
        }
        if (2 < g_switch_debug_level) {
          printk("sw_del_igmp_addr_e8v4 1portmask %d\n",uVar1);
        }
        tm_ipv4table_delete_set(&local_3c);
        sw_igmp_mulrule_deal(uVar4,uVar3,0);
        return 0;
      }
      if (g_switch_debug_level != 0) {
        printk("tm_ipv4table_lookup_get ERROR: sip=%d, dip=%d, vlan_id=%d\n",local_38,local_34,
               local_30);
        return 0xffffffff;
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("get_sw_port_from_devname curPort ERROR: portname=%s\n",&local_4c);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

