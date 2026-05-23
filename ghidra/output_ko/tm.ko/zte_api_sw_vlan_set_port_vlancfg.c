// module: tm.ko
// function: zte_api_sw_vlan_set_port_vlancfg @ 0x643bc
// size: 128 bytes
//

undefined4 zte_api_sw_vlan_set_port_vlancfg(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_4 == 0) {
    uVar2 = 2;
  }
  else if (param_4 == 1) {
    uVar2 = 1;
  }
  else if (param_4 == 2) {
    uVar2 = 0;
  }
  else {
    uVar2 = 3;
  }
  do {
    if (param_3 < param_2) {
      return 0;
    }
    iVar1 = tm_vlantable_add_set(param_1,uVar2,param_2);
    param_2 = param_2 + 1;
  } while (iVar1 == 0);
  printk("[%s] L%d tm sdk failed!\n","zte_api_sw_vlan_set_port_vlancfg",0x5c9);
  return 0xffffffff;
}

