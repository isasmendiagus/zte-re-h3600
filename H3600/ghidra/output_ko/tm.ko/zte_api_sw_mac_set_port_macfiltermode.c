// module: tm.ko
// function: zte_api_sw_mac_set_port_macfiltermode @ 0x64be0
// size: 188 bytes
//

undefined4
zte_api_sw_mac_set_port_macfiltermode
          (uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  if (param_2 == 4) {
    iVar1 = tm_port_clear_macaddr_set(1 << (param_1 & 0xff));
    iVar2 = tm_mac_sa_lookfail_ctrl_set(param_1,0);
    if (iVar2 != 0 || iVar1 != 0) {
      printk("%s %d set macfilter mode SA WHITE failed!\n","zte_api_sw_mac_set_port_macfiltermode",
             0x95b);
      return 0xffffffff;
    }
  }
  else if (param_2 == 2) {
    printk("not support DA WIHTE mode now\n");
  }
  else {
    bVar3 = 2 < param_2;
    if (param_2 != 3) {
      bVar3 = param_2 != 0;
    }
    if (bVar3 && (param_2 != 3 && param_2 != 1)) {
      printk("invaild mac filter mode\n");
      return 0xffffffff;
    }
    iVar1 = tm_mac_sa_lookfail_ctrl_set(param_1,1,param_3,param_4,param_4);
    if (iVar1 != 0) {
      printk("%s %d tm sdk failed!\n","zte_api_sw_mac_set_port_macfiltermode",0x96a);
      return 0xffffffff;
    }
  }
  return 0;
}

