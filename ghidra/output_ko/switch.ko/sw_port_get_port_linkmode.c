// module: switch.ko
// function: sw_port_get_port_linkmode @ 0x17bdc
// size: 260 bytes
//

undefined4 sw_port_get_port_linkmode(int *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  byte local_13;
  byte local_12;
  byte local_11;
  
  local_13 = 0;
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_port_get_port_linkmode","LinkMode.port",*param_1);
  }
  iVar2 = zte_api_sw_port_get_port_linkmode
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],&local_13,&local_12,&local_11);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[1] = (uint)local_13;
    param_1[2] = (uint)local_12;
    param_1[3] = (uint)local_11;
    uVar3 = 0;
    if (2 < uVar1) {
      printk("[%s] output:\n%s = %d\n%s = %d\n%s = %d\n","sw_port_get_port_linkmode",
             "LinkMode.autoneg",(uint)local_13,"LinkMode.speed",(uint)local_12,"LinkMode.duplex",
             (uint)local_11);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_linkmode",0x1d9);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

