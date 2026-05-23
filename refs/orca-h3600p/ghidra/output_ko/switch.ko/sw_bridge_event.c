// module: switch.ko
// function: sw_bridge_event @ 0x12f44
// size: 260 bytes
//

undefined4 sw_bridge_event(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  uint local_14;
  
  puVar3 = (undefined1 *)*param_3;
  uVar2 = param_3[2];
  local_14 = 0;
  if (param_2 == 2) {
    iVar1 = get_sw_port_from_devname(uVar2,&local_14,1);
    if (iVar1 == 0) {
      if (2 < g_switch_debug_level) {
        printk("switch clear mac [%02x:%02x:%02x:%02x:%02x:%02x],port_dev.name %s,port=%d\n",*puVar3
               ,puVar3[1],puVar3[2],puVar3[3],puVar3[4],puVar3[5],uVar2,local_14);
      }
      iVar1 = zte_api_sw_mac_del_port_macaddress(local_14 & 0xff,puVar3,0,0);
      if ((iVar1 != 0) && (2 < g_switch_debug_level)) {
        printk("[%s] L%d  failed!\n","sw_bridge_event",0x9e);
      }
    }
    else if (2 < g_switch_debug_level) {
      printk("get_sw_port_from_devname fail, dev name %s\n",uVar2);
    }
  }
  return 0;
}

