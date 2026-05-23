// module: tm.ko
// function: zte_api_sw_port_set_port_multicastrate @ 0x6327c
// size: 200 bytes
//

undefined4
zte_api_sw_port_set_port_multicastrate
          (uint param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6,
          char param_7)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (param_1 < 8) {
    if (param_5 == 0 && param_6 == 0) {
      param_3 = 0;
    }
    if (param_2 == 0) {
      uVar1 = 0;
      if (param_7 != '\0') {
        uVar1 = 0x18;
      }
      iVar3 = sadm_set_spend_byte(uVar1);
      if (iVar3 != 0) {
        printk("sadm_set_spend_byte fail!\n");
        return 0xffffffff;
      }
      if (param_3 == 0) {
        param_5 = 0;
        param_6 = 0;
      }
      tm_port_cast_rate_limit_set(param_1,param_3,param_5,param_6,2);
    }
    else if (param_2 - 1U < 2) {
      printk("egress multicast ratelimit no support!\n");
      return 0;
    }
    uVar2 = 0;
  }
  else {
    printk("zte_api_sw_port_set_port_multicastrate:Invalid Switch Port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

