// module: tm.ko
// function: greg_get_lpi_inir @ 0x31ef0
// size: 156 bytes
//

undefined4 greg_get_lpi_inir(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (4 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_get_brg2swgreg_init] input invalid parameter,intrno = %d!\n",param_1);
    return 1;
  }
  iVar1 = tmOnuRegRead(param_1 + 7 & 0xff,param_2,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("greg_get_brg2swgreg_init] greg_read_reg failed,ret= %d!\n");
  return 0xffffffff;
}

