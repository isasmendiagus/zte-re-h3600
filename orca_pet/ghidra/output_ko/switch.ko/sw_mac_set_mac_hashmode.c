// module: switch.ko
// function: sw_mac_set_mac_hashmode @ 0x1561c
// size: 104 bytes
//

undefined4 sw_mac_set_mac_hashmode(undefined1 *param_1)

{
  int iVar1;
  
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_mac_set_mac_hashmode",
           "MacHashMode.hashMode(0-mac 1-mac+vlan)",*param_1);
  }
  iVar1 = tm_hash_mode_set(*param_1);
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","sw_mac_set_mac_hashmode",0x2b3);
  return 0xffffffff;
}

