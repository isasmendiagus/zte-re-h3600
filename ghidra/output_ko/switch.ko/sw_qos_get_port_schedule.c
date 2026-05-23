// module: switch.ko
// function: sw_qos_get_port_schedule @ 0x18b20
// size: 252 bytes
//

undefined4 sw_qos_get_port_schedule(int *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  byte local_12;
  byte local_11;
  
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n","sw_qos_get_port_schedule","Schedule.port",*param_1,
           "Schedule.queue",param_1[1]);
  }
  iVar2 = zte_api_sw_qos_get_port_schedule
                    (zte_api_sw_mac_set_port_macfiltermode[*param_1],(char)param_1[1],&local_12,
                     &local_11);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[2] = (uint)local_12;
    param_1[3] = (uint)local_11;
    uVar3 = 0;
    if (2 < uVar1) {
      printk("[%s] output:\n%s = %d\n%s = %d\n","sw_qos_get_port_schedule",
             "Schedule.mode(1-sp 0-dwrr)",(uint)local_12,"Schedule.weight",(uint)local_11);
    }
  }
  else {
    printk("%s failed!\n","sw_qos_get_port_schedule");
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

