// module: switch.ko
// function: sw_mac_set_onu_stpaction @ 0x14540
// size: 196 bytes
//

undefined4 sw_mac_set_onu_stpaction(undefined1 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  undefined4 uVar6;
  uint local_1e;
  undefined2 local_1a;
  
  uVar1 = *param_1;
  uVar2 = param_1[0xc];
  __memzero(&local_1e,6);
  local_1e = *(uint *)(param_1 + 4);
  local_1a = *(undefined2 *)(param_1 + 8);
  if (2 < g_switch_debug_level) {
    local_1a._1_1_ = (undefined1)((ushort)local_1a >> 8);
    uVar3 = local_1a._1_1_;
    uVar4 = (undefined1)local_1a;
    printk("[%s] input:\n mode = %d mac = %2x:%2x:%2x:%2x:%2x:%2x action = %d\n",
           "sw_mac_set_onu_stpaction",uVar1,local_1e & 0xff,local_1e >> 8 & 0xff,
           local_1e >> 0x10 & 0xff,local_1e >> 0x18,uVar4,uVar3,uVar2);
  }
  iVar5 = zte_api_sw_mac_set_onu_stpaction(uVar1,&local_1e,uVar2);
  uVar6 = 0;
  if (iVar5 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_mac_set_onu_stpaction",0x88);
    uVar6 = 0xffffffff;
  }
  return uVar6;
}

