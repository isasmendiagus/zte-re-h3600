// module: switch.ko
// function: sw_port_set_port_isolatemask @ 0x178d0
// size: 256 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_set_port_isolatemask(int *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = param_1[1];
  uVar2 = (uint)(byte)tm_set_p2pmode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = 0x%x\n","sw_port_set_port_isolatemask","IsolateMask.port",
           uVar2,"IsolateMask.portmask",uVar3);
  }
  if ((_eth_type_trans & 1 << uVar2) == 0) {
    if (g_switch_debug_level != 0) {
      printk("[%s] input invalid port!\n","sw_port_set_port_isolatemask");
      return 0xffffffff;
    }
  }
  else {
    if (uVar3 <= _eth_type_trans) {
      iVar1 = zte_api_sw_port_set_port_isolatemask(uVar2,uVar3);
      if (iVar1 == 0) {
        return 0;
      }
      printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_isolatemask",0x165);
      return 0xffffffff;
    }
    if (g_switch_debug_level != 0) {
      printk("[%s] input invalid portmask!\n","sw_port_set_port_isolatemask");
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

