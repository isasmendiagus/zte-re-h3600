// module: switch.ko
// function: sw_mac_set_port_learnlimit @ 0x14700
// size: 176 bytes
//

undefined4 sw_mac_set_port_learnlimit(int *param_1)

{
  code cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = param_1[1];
  iVar3 = param_1[2];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n","sw_mac_set_port_learnlimit","LearnLimit.port"
           ,*param_1,"LearnLimit.enable",uVar4,"LearnLimit.limit",iVar3);
  }
  iVar3 = zte_api_sw_mac_set_port_learnlimit(cVar1,uVar4 & 0xff,iVar3);
  uVar2 = 0;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_mac_set_port_learnlimit",0x56);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

