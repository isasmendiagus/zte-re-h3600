// module: switch.ko
// function: sw_qos_get_availbktid @ 0x18f24
// size: 220 bytes
//

undefined4 sw_qos_get_availbktid(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_14 [2];
  
  local_14[0] = 0;
  if (param_1 == (int *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("sw_qos_get_availbktid input ERROR!\nioctl_data_sweth=NULL\n");
    }
    return 0xffffffff;
  }
  iVar1 = zte_api_sw_qos_get_availbktid(local_14);
  if (iVar1 == 0) {
    if (local_14[0] == 0x20) {
      if (g_switch_debug_level == 0) {
        return 0xffffffff;
      }
      printk("sw_qos_get_availbktid return ERROR!\nno avail bucket\n");
      uVar2 = 0xffffffff;
    }
    else {
      *param_1 = local_14[0];
      uVar2 = 0;
      if (2 < g_switch_debug_level) {
        printk("sw_qos_get_availbktid output:\nbucket index=%d\n");
      }
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_qos_get_availbktid",0x150);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

