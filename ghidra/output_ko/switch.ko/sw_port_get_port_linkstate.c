// module: switch.ko
// function: sw_port_get_port_linkstate @ 0x17ce4
// size: 284 bytes
//

undefined4 sw_port_get_port_linkstate(int *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  byte local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  local_13 = 0;
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_port_get_port_linkstate","LinkState.port",*param_1);
  }
  iVar2 = zte_api_sw_port_get_port_linkstate
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],&local_13,&local_12,&local_11);
  if (iVar2 == 0) {
    param_1[1] = (uint)local_13;
    iVar2 = sw_ztespeed_to_cspplatspeed(local_12);
    param_1[2] = iVar2;
    iVar2 = sw_zteduplex_to_cspplatduplex(local_11);
    uVar1 = g_switch_debug_level;
    param_1[3] = iVar2;
    uVar3 = 0;
    if (2 < uVar1) {
      printk("[%s] output:\n%s = %d\n%s = %d\n%s = %d\n","sw_port_get_port_linkstate",
             "LinkState.link",param_1[1],"LinkState.speed",param_1[2],"LinkState.duplex",iVar2);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_linkstate",0x1fb);
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

