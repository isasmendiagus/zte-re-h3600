// module: switch.ko
// function: sw_port_get_port_loopback @ 0x181d0
// size: 220 bytes
//

int sw_port_get_port_loopback(int *param_1)

{
  uint uVar1;
  int iVar2;
  byte local_12;
  byte local_11;
  
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_port_get_port_loopback","LoopBack.port",*param_1);
  }
  iVar2 = zte_api_sw_port_get_port_loopback(tm_set_p2pmode[*param_1],&local_11,&local_12);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[1] = (uint)local_12;
    param_1[2] = (uint)local_11;
    if (2 < uVar1) {
      printk("[%s] output:\n%s = %d\n%s = %d\n","sw_port_get_port_loopback","LoopBack.direct",
             (uint)local_11,"LoopBack.enable",(uint)local_12);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_loopback",0x29d);
  }
  return iVar2;
}

