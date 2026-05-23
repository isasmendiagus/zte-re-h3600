// module: switch.ko
// function: sw_mac_set_onu_agingtime @ 0x14604
// size: 112 bytes
//

undefined4 sw_mac_set_onu_agingtime(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *param_1;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_mac_set_onu_agingtime","AgingTime.time",uVar2);
  }
  iVar1 = zte_api_sw_mac_set_onu_agingtime(uVar2);
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","sw_mac_set_onu_agingtime",0x2d);
  return 0xffffffff;
}

