// module: switch.ko
// function: sw_add_igmp_addr_e8v4 @ 0x1f96c
// size: 488 bytes
//

undefined4 sw_add_igmp_addr_e8v4(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  uint local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&local_44,0x10);
    local_44 = *param_1;
    local_40 = param_1[1];
    local_3c = param_1[2];
    local_38 = param_1[3];
    if (2 < g_switch_debug_level) {
      printk("sw_add_igmp_addr_e8v4 portname %s\n",&local_44);
    }
    iVar2 = get_sw_port_from_devname(&local_44,&local_48,1);
    if (iVar2 == 0) {
      uVar1 = 1 << (local_48 & 0xff);
      uVar4 = param_1[5];
      uVar3 = *(ushort *)(param_1 + 4) & 0xfff;
      if (2 < g_switch_debug_level) {
        printk("sw_add_igmp_addr_e8v4 portMsk 0x%8.8x, sip 0x%8.8x, dip 0x%8.8x, vlan %d\n",uVar1,0,
               uVar4,uVar3);
      }
      __memzero(&local_34);
      local_30 = 0;
      local_2c = uVar4;
      local_28 = uVar3;
      iVar2 = tm_ipv4table_lookup_get(&local_34);
      if (iVar2 == 0) {
        if (g_switch_debug_level < 3) {
          local_24 = uVar1 | local_24;
        }
        else {
          printk("tm_ipv4table_lookup_get, l_portMsk=%d\n",local_24);
          local_24 = uVar1 | local_24;
          if (2 < g_switch_debug_level) {
            printk("after, l_portMsk=%d\n",local_24);
          }
        }
        local_33 = 0;
        local_34 = 1;
        local_32 = 1;
        tm_ipv4table_add_set(&local_34);
        sw_igmp_mulrule_deal(uVar4,uVar3,1);
        return 0;
      }
      if (g_switch_debug_level != 0) {
        printk("tm_ipv4table_lookup_get ERROR: sip=%d, dip=%d, vlan_id=%d\n",local_30,local_2c,
               local_28);
      }
    }
    else if (g_switch_debug_level != 0) {
      printk("get_sw_port_from_devname curPort ERROR: portname=%s\n",&local_44);
    }
  }
  return 0xffffffff;
}

