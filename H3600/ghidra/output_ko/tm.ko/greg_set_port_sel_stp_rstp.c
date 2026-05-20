// module: tm.ko
// function: greg_set_port_sel_stp_rstp @ 0x32830
// size: 164 bytes
//

undefined4
greg_set_port_sel_stp_rstp(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = param_2 != 0;
  bVar2 = param_2 == 1;
  if (param_2 < 2) {
    bVar3 = 5 < param_1;
    bVar2 = param_1 == 6;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][greg_set_port_sel_stp_rstp] input invalid parameter,port= %d!\n",param_1);
      return 1;
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(param_1 + 0x24 & 0xff,param_2,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][greg_set_port_sel_stp_rstp] GREG_WRITE_REG( failed,ret= %d!\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

