// module: switch.ko
// function: sw_port_set_ethdev_carrier @ 0x18804
// size: 124 bytes
//

undefined4 sw_port_set_ethdev_carrier(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    if (g_switch_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[SW][sw_port_set_ethdev_carrier] input ERROR: ioctl_data_sweth=null\n");
    return 0xffffffff;
  }
  g_ethdev_carrierFlag = *param_1;
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("[SW][sw_port_set_ethdev_carrier] input: g_ethdev_carrierFlag %d \n");
  return 0;
}

