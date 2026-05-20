// module: tm.ko
// function: zte_api_sw_mac_set_onu_stpaction @ 0x64d30
// size: 92 bytes
//

undefined4 zte_api_sw_mac_set_onu_stpaction(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  if (param_3 != 1) {
    if (param_3 == 0) {
      param_3 = 0;
    }
    else if (param_3 != 2) {
      printk("invaid action type\n");
      return 0xffffffff;
    }
  }
  iVar1 = spa_set_stp_action(param_3);
  if (iVar1 != 0) {
    printk("[%s]tm sdk failed!\n","zte_api_sw_mac_set_onu_stpaction");
    return 0xffffffff;
  }
  return 0;
}

