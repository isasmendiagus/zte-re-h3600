// module: switch.ko
// function: sw_set_trap_cpu_ip @ 0x22040
// size: 76 bytes
//

undefined4 sw_set_trap_cpu_ip(int *param_1)

{
  if (*param_1 != 0) {
    sw_update_match_rule_ip();
    return 0;
  }
  if (g_switch_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[SW][sw_set_trap_cpu_ip] input ERROR: ip is zero\n");
  return 0xffffffff;
}

