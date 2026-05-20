// module: switch.ko
// function: sw_other_set_onu_mtu @ 0x16748
// size: 136 bytes
//

undefined4 sw_other_set_onu_mtu(uint *param_1)

{
  int iVar1;
  code *pcVar2;
  uint uVar3;
  
  uVar3 = *param_1;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_other_set_onu_mtu","Mtu.mtusize",uVar3);
  }
  pcVar2 = (code *)((int)&tm_set_p2pmode + 3);
  if (1999 < uVar3) {
    uVar3 = 2000;
  }
  do {
    pcVar2 = pcVar2 + 1;
    iVar1 = zte_api_sw_other_set_onu_mtu(*pcVar2,uVar3);
    if (iVar1 != 0) {
      printk("[%s] L%d tm sdk failed!\n","sw_other_set_onu_mtu",0xbf);
      return 0xffffffff;
    }
  } while (pcVar2 != zte_api_sw_vlan_get_port_inframemode);
  return 0;
}

