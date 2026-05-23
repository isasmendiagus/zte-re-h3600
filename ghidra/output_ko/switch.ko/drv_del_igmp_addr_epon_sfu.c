// module: switch.ko
// function: drv_del_igmp_addr_epon_sfu @ 0x1c238
// size: 420 bytes
//

undefined4 drv_del_igmp_addr_epon_sfu(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
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
    uVar3 = 0xffffffff;
    printk("[SW][drv_add_igmp_addr] input ERROR: igmpEntry=null\n");
  }
  else {
    iVar2 = get_sw_port_from_devname(param_1,&local_24,1);
    if (iVar2 == -1) {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("%s %d Error\n","drv_del_igmp_addr_epon_sfu",0x16f);
      uVar3 = 0xffffffff;
    }
    else {
      uVar4 = *(uint *)(param_1 + 0x14);
      uVar1 = *(undefined2 *)(param_1 + 0x10);
      if (2 < g_switch_debug_level) {
        printk("[SW][drv_add_igmp_addr] IGMP_dip = %x, IGMP_vlan = %d \n",uVar4,uVar1);
      }
      __memzero(&local_1e,6);
      local_1b = (byte)(uVar4 >> 0x10) & 0x7f;
      local_19 = (undefined1)uVar4;
      local_1e = 1;
      local_1d = 0;
      local_1c = 0x5e;
      local_1a = (undefined1)(uVar4 >> 8);
      if (((2 < g_switch_debug_level) &&
          (printk("[SW][change_portmask] IGMP_dip & 0xff = %d\n",uVar4 & 0xff),
          2 < g_switch_debug_level)) &&
         (printk("[SW][change_portmask] IGMP_dip>> 8 & 0xff = %d\n",uVar4 >> 8 & 0xff),
         2 < g_switch_debug_level)) {
        printk("[SW][change_portmask] IGMP_dip>> 16 & 0xff = %d\n",uVar4 >> 0x10 & 0xff);
      }
      iVar2 = zte_api_sw_mac_del_port_macaddress(local_24 & 0xff,&local_1e,uVar1,0);
      if (iVar2 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = 0xffffffff;
        printk("zte_api_sw_mac_del_port_macaddress failed!\n");
      }
    }
  }
  return uVar3;
}

