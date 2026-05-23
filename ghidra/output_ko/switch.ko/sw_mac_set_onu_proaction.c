// module: switch.ko
// function: sw_mac_set_onu_proaction @ 0x14574
// size: 108 bytes
//

undefined4
sw_mac_set_onu_proaction
          (undefined1 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  
  uVar1 = *param_1;
  uVar2 = param_1[4];
  if (2 < g_switch_debug_level) {
    printk("[%s] input type %d action %d\n","sw_mac_set_onu_proaction",uVar1,uVar2,param_4);
  }
  iVar3 = zte_api_sw_mac_set_onu_proaction(uVar1,uVar2);
  if (iVar3 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","sw_mac_set_onu_proaction",0xa1);
  return 0xffffffff;
}

