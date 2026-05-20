// module: tm.ko
// function: tm_show_one_common_rule_config @ 0x67a18
// size: 92 bytes
//

void tm_show_one_common_rule_config(int param_1)

{
  int *piVar1;
  
  for (piVar1 = g_AclFilter_Head; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0x12e]) {
    if (*piVar1 == param_1) {
      tm_print_common_rule_config(piVar1);
      return;
    }
  }
  if (g_tm_debug_level == 0) {
    return;
  }
  printk("Invalid index! \n");
  return;
}

