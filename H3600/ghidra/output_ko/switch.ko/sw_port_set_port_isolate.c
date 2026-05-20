// module: switch.ko
// function: sw_port_set_port_isolate @ 0x177b8
// size: 100 bytes
//

undefined4 sw_port_set_port_isolate(undefined4 *param_1)

{
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("[%s] input:\n%s = %d\n%s = %d\n","sw_port_set_port_isolate","Isolate.port",*param_1,
         "Isolate.enable",param_1[1]);
  return 0;
}

