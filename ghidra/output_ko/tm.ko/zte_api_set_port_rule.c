// module: tm.ko
// function: zte_api_set_port_rule @ 0x64d90
// size: 64 bytes
//

undefined4 zte_api_set_port_rule(void)

{
  int iVar1;
  
  iVar1 = tm_pm_port_rule_set();
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][zte_api_set_port_rule]failed!\n");
  return 0xffffffff;
}

