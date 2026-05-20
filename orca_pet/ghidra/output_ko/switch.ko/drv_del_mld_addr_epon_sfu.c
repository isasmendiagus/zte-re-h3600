// module: switch.ko
// function: drv_del_mld_addr_epon_sfu @ 0x1c648
// size: 468 bytes
//

undefined4 drv_del_mld_addr_epon_sfu(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  uint local_24;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_24 = 0;
  if (param_1 == 0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    uVar2 = 0xffffffff;
    printk("[SW][drv_del_mld_addr] input ERROR: mldEntry=null\n");
  }
  else {
    iVar1 = get_sw_port_from_devname(param_1,&local_24,1);
    if (iVar1 == -1) {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("%s %d Error\n","drv_del_mld_addr_epon_sfu",0x1e6);
      uVar2 = 0xffffffff;
    }
    else {
      if (g_switch_debug_level < 3) {
        uVar3 = *(undefined2 *)(param_1 + 0x10);
      }
      else {
        printk("[SW][drv_del_mld_addr] portName = %s, dwPort = %d \n",param_1,local_24);
        uVar3 = *(undefined2 *)(param_1 + 0x10);
        if (2 < g_switch_debug_level) {
          printk("[SW][drv_del_mld_addr] IGMP_vlan = %d\n",uVar3);
        }
      }
      __memzero(&local_1e,6);
      local_1c = *(undefined1 *)(param_1 + 0x1e);
      local_1b = *(undefined1 *)(param_1 + 0x1f);
      local_1a = *(undefined1 *)(param_1 + 0x20);
      local_19 = *(undefined1 *)(param_1 + 0x21);
      local_1e = 0x33;
      local_1d = 0x33;
      if ((((2 < g_switch_debug_level) &&
           (printk("[SW][drv_del_mld_addr] p1 = %d\n"), 2 < g_switch_debug_level)) &&
          (printk("[SW][drv_del_mld_addr] p2 = %d\n",*(undefined1 *)(param_1 + 0x1f)),
          2 < g_switch_debug_level)) &&
         (printk("[SW][drv_del_mld_addr] p3 = %d\n",*(undefined1 *)(param_1 + 0x20)),
         2 < g_switch_debug_level)) {
        printk("[SW][drv_del_mld_addr] p4 = %d\n",*(undefined1 *)(param_1 + 0x21));
      }
      iVar1 = zte_api_sw_mac_del_port_macaddress(local_24 & 0xff,&local_1e,uVar3,0);
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

