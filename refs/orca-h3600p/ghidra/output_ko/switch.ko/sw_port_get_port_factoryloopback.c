// module: switch.ko
// function: sw_port_get_port_factoryloopback @ 0x18358
// size: 256 bytes
//

int sw_port_get_port_factoryloopback(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  byte local_12;
  byte local_11;
  
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_port_get_port_factoryloopback","LoopBack.port",*param_1);
  }
  iVar2 = zte_api_sw_port_get_port_loopback(*(undefined1 *)param_1,&local_11,&local_12);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    uVar3 = (uint)local_12;
    param_1[1] = uVar3;
    param_1[2] = (uint)local_11;
    if (2 < uVar1) {
      pcVar4 = "LoopBack.enable";
      printk("\n[%s] output:\n%s = %d\n%s = %d\n","sw_port_get_port_factoryloopback",
             "LoopBack.direct",(uint)local_11,"LoopBack.enable",uVar3);
      if (2 < g_switch_debug_level) {
        printk("%s = %c\n","phy_notcarelink",0x41,g_switch_debug_level,pcVar4,uVar3);
        return 0;
      }
    }
    iVar2 = 0;
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_factoryloopback",0x2da);
  }
  return iVar2;
}

