// module: switch.ko
// function: sw_mac_get_port_learnlimit @ 0x14868
// size: 228 bytes
//

undefined4 sw_mac_get_port_learnlimit(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  byte local_15;
  int local_14;
  
  cVar1 = tm_set_p2pmode[*param_1];
  local_15 = 0;
  local_14 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_mac_get_port_learnlimit","LearnLimit.port");
  }
  iVar3 = zte_api_sw_mac_get_port_learnlimit(cVar1,&local_15,&local_14);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    param_1[1] = (uint)local_15;
    param_1[2] = local_14;
    uVar4 = 0;
    if (2 < uVar2) {
      printk("[%s] output:\n%s = %d\n%s = %d\n","sw_mac_get_port_learnlimit","LearnLimit.enable",
             (uint)local_15,"LearnLimit.limit",local_14);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_mac_get_port_learnlimit",0x6a);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}

