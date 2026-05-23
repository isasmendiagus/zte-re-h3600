// module: tm.ko
// function: sbrg_set_srcaddr_aging_cycle @ 0x19938
// size: 128 bytes
//

undefined4
sbrg_set_srcaddr_aging_cycle(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 < 4) {
    param_1 = 4;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_set_srcaddr_aging_cycle]input:age_cycle = %d\n",param_1,param_3,
           g_tm_debug_level,param_4);
  }
  iVar1 = tmOnuRegWrite(0x1e,param_1,0,&sbragRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_set_srcaddr_aging_cycle]write reg failed!\n");
  return 0xffffffff;
}

