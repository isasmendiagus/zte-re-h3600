// module: switch.ko
// function: sw_qos_set_port_schedule @ 0x18ae0
// size: 208 bytes
//

undefined4 sw_qos_set_port_schedule(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n","sw_qos_set_port_schedule",
           "Schedule.port",*param_1,"Schedule.queue",param_1[1],"Schedule.mode(0-sp 1-dwrr)",
           param_1[2],"Schedule.weight",param_1[3]);
  }
  iVar1 = zte_api_sw_qos_set_port_schedule
                    (tm_set_p2pmode[*param_1],(char)param_1[1],(char)param_1[2],(char)param_1[3]);
  uVar2 = 0;
  if (iVar1 != 0) {
    printk("%s failed!\n","sw_qos_set_port_schedule");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

