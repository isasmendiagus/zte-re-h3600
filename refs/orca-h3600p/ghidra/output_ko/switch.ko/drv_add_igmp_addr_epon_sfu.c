// module: switch.ko
// function: drv_add_igmp_addr_epon_sfu @ 0x1c0f8
// size: 460 bytes
//

undefined4 drv_add_igmp_addr_epon_sfu(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined2 uVar4;
  uint local_24;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  byte local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_24 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("[SW][drv_add_igmp_addr] input ERROR: igmpEntry=null\n");
  }
  else {
    iVar1 = get_sw_port_from_devname(param_1,&local_24,1);
    if (iVar1 == -1) {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("%s %d Error\n","drv_add_igmp_addr_epon_sfu",0x133);
      uVar2 = 0xffffffff;
    }
    else {
      if (g_switch_debug_level < 3) {
        uVar3 = *(uint *)(param_1 + 0x14);
        uVar4 = *(undefined2 *)(param_1 + 0x10);
      }
      else {
        printk("[SW][drv_add_igmp_addr] portname = %s, dwPort = %d \n",param_1,local_24);
        uVar3 = *(uint *)(param_1 + 0x14);
        uVar4 = *(undefined2 *)(param_1 + 0x10);
        if (2 < g_switch_debug_level) {
          printk("[SW][drv_add_igmp_addr] IGMP_dip = %x, IGMP_vlan = %d \n",uVar3,uVar4);
        }
      }
      __memzero(&local_1e,6);
      local_1b = (byte)(uVar3 >> 0x10) & 0x7f;
      local_19 = (undefined1)uVar3;
      local_1e = 1;
      local_1d = 0;
      local_1c = 0x5e;
      local_1a = (undefined1)(uVar3 >> 8);
      if (((2 < g_switch_debug_level) &&
          (printk("[SW][drv_add_igmp_addr] p1 = %d\n",uVar3 & 0xff), 2 < g_switch_debug_level)) &&
         (printk("[SW][drv_add_igmp_addr] p2 = %d\n",uVar3 >> 8 & 0xff), 2 < g_switch_debug_level))
      {
        printk("[SW][drv_add_igmp_addr] p3 = %d\n",uVar3 >> 0x10 & 0xff);
      }
      iVar1 = zte_api_sw_mac_add_port_macaddress(local_24 & 0xff,&local_1e,uVar4,0);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = 0xffffffff;
        printk("zte_api_sw_mac_add_port_macaddress failed!\n");
      }
    }
  }
  return uVar2;
}

