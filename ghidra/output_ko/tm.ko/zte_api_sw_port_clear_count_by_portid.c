// module: tm.ko
// function: zte_api_sw_port_clear_count_by_portid @ 0x6210c
// size: 92 bytes
//

undefined4
zte_api_sw_port_clear_count_by_portid
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = smac_set_cnt_rst(param_1,1,param_3,param_4,param_4);
  if (iVar1 == 0) {
    iVar1 = smac_set_cnt_rst(param_1,0);
    uVar2 = 0;
    if (iVar1 != 0) {
      uVar2 = 0xffffffff;
      printk("set smac clear disable failed\n");
    }
  }
  else {
    uVar2 = 0xffffffff;
    printk("set smac clear enable failed\n");
  }
  return uVar2;
}

