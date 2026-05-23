// module: tm.ko
// function: zte_api_sw_mac_get_onu_agingtime @ 0x64acc
// size: 40 bytes
//

undefined4 zte_api_sw_mac_get_onu_agingtime(void)

{
  int iVar1;
  
  iVar1 = tm_mac_aging_cycle_get();
  if (iVar1 == 0) {
    return 0;
  }
  printk("[%s]tm sdk failed!\n","zte_api_sw_mac_get_onu_agingtime");
  return 0xffffffff;
}

