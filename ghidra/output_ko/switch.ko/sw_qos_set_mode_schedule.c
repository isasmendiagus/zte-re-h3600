// module: switch.ko
// function: sw_qos_set_mode_schedule @ 0x192ec
// size: 188 bytes
//

int sw_qos_set_mode_schedule(undefined1 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  if (1 < g_switch_debug_level) {
    printk("the function:%s, the parameters coming in as follows:\n%s = %d, %s = %d\n",
           "sw_qos_set_mode_schedule",&_LC37,uVar1,"queue_id",uVar2);
  }
  if ((g_pon_work_mode & 0x10) == 0) {
    iVar3 = pon_driver_adapter_schedue_mode_set(uVar1);
  }
  else {
    iVar3 = wan_driver_adapter_schedue_mode_set(uVar2,uVar1);
  }
  if ((iVar3 != 0) && (g_switch_debug_level != 0)) {
    printk("the function:%s, qos set mode failed\n","sw_qos_set_mode_schedule");
  }
  return iVar3;
}

