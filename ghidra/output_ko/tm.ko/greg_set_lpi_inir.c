// module: tm.ko
// function: greg_set_lpi_inir @ 0x31e54
// size: 156 bytes
//

undefined4 greg_set_lpi_inir(uint param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = 3 < param_1;
  bVar2 = param_1 == 4;
  if (param_1 < 5) {
    bVar3 = param_2 != 0;
    bVar2 = param_2 == 1;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][greg_set_brg2swgreg_init] input invalid parameter,en = %d!\n");
      return 1;
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(param_1 + 7 & 0xff,param_2,0,&gregRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("greg_set_brg2swgreg_init] GREG_WRITE_REG( failed,ret= %d!\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

