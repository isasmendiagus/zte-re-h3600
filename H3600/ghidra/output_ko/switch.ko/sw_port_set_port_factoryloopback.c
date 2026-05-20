// module: switch.ko
// function: sw_port_set_port_factoryloopback @ 0x18220
// size: 164 bytes
//

int sw_port_set_port_factoryloopback(undefined1 *param_1)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = *param_1;
  uVar3 = *(uint *)(param_1 + 4);
  uVar4 = *(uint *)(param_1 + 8);
  if (2 < g_switch_debug_level) {
    printk("\n[%s] input:\n%s = %d\n%s = %d\n%s = %d\n","sw_port_set_port_factoryloopback",
           "LoopBack.port",uVar1,"LLoopBack.enable",uVar3,"LoopBack.direct",uVar4);
  }
  iVar2 = zte_api_sw_port_set_port_loopback(uVar1,uVar4 & 0xff,uVar3 & 0xff);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_factoryloopback",0x2ab);
  }
  return iVar2;
}

