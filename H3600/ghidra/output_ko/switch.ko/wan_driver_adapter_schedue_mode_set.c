// module: switch.ko
// function: wan_driver_adapter_schedue_mode_set @ 0x191fc
// size: 236 bytes
//

int wan_driver_adapter_schedue_mode_set
              (uint param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (7 < param_1) {
    printk("queue_id = %d  >= QUEUE_SIZE=%d\n",param_1,8,param_4,param_4);
    return -1;
  }
  *(char *)((int)&g_queue_mode + param_1) = (char)param_2;
  iVar1 = sw_qos_vdsl_up();
  if (iVar1 == 0) {
    if ((param_2 != 1) && (param_2 == 2)) {
      param_2 = 0;
    }
    iVar1 = zte_api_sw_qos_set_port_schedule(tm_vlan_check_ena_set,param_1,param_2,0);
  }
  else {
    if (param_2 == 1) {
      param_2 = 0;
    }
    else if (param_2 == 2) {
      param_2 = 1;
    }
    iVar1 = tm_tcont_que_sch_sp_dwwr_mod_set(0,param_1,param_2);
  }
  if ((iVar1 != 0) && (g_switch_debug_level != 0)) {
    printk("The function %s line:%d is error :%d\n","wan_driver_adapter_schedue_mode_set",0x348,
           iVar1,param_4);
    return iVar1;
  }
  return iVar1;
}

