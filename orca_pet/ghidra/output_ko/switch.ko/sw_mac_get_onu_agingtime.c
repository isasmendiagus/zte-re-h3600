// module: switch.ko
// function: sw_mac_get_onu_agingtime @ 0x14728
// size: 136 bytes
//

undefined4 sw_mac_get_onu_agingtime(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = zte_api_sw_mac_get_onu_agingtime(local_14);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (2 < g_switch_debug_level) {
      printk("[%s] output:\n%s = %d\n","sw_mac_get_onu_agingtime","AgingTime.time");
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_mac_get_onu_agingtime",0x3b);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

