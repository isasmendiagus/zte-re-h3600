// module: tm.ko
// function: zte_api_sw_other_set_onu_mtu @ 0x62808
// size: 208 bytes
//

undefined4 zte_api_sw_other_set_onu_mtu(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  if (param_2 < 5) {
    printk("mtu too small\n");
    return 0xffffffff;
  }
  uVar1 = fpga_read_reg(0x10006);
  if (lan_up == 0) {
    if ((uVar1 & 3) == 0) {
      uVar1 = fpga_read_reg(0x34001);
      fpga_write_reg(0x34001,uVar1 & 0xffffc000 | param_2);
    }
    else if ((uVar1 & 3) == 1) {
      uVar1 = fpga_read_reg(0x20041);
      fpga_write_reg(0x20041,uVar1 & 0xfffff800 | param_2);
    }
  }
  iVar2 = sdet_set_maxframe_length(param_1,param_2 - 4);
  if (iVar2 == 0) {
    return 0;
  }
  printk("[%s]tm sdk failed!\n","zte_api_sw_other_set_onu_mtu");
  return 0xffffffff;
}

