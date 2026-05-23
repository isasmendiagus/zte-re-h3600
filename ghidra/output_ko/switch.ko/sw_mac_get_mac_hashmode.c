// module: switch.ko
// function: sw_mac_get_mac_hashmode @ 0x155d4
// size: 136 bytes
//

undefined4 sw_mac_get_mac_hashmode(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_11 [5];
  
  local_11[0] = 0;
  iVar1 = tm_hash_mode_get(local_11);
  if (iVar1 == 0) {
    *param_1 = local_11[0];
    uVar2 = 0;
    if (2 < g_switch_debug_level) {
      printk("[%s] output:\n%s = %d\n","sw_mac_get_mac_hashmode",
             "MacHashMode.hashMode(0-mac 1-mac+vlan)");
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_mac_get_mac_hashmode",0x2c2);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

