// module: tm.ko
// function: greg_get_port_need_authen @ 0x32be0
// size: 156 bytes
//

undefined4
greg_get_port_need_authen(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_get_port_need_authen] input invalid parameter,port= %d!\n",param_1);
    return 1;
  }
  iVar1 = tmOnuRegRead(param_1 + 0x32 & 0xff,param_2,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][greg_get_port_need_authen] greg_read_reg failed,ret= %d!\n");
  return 0xffffffff;
}

