// module: tm.ko
// function: sdet_set_soft_vid @ 0x365b0
// size: 280 bytes
//

undefined4 sdet_set_soft_vid(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  bool bVar2;
  
  bVar2 = 6 < param_2;
  if (param_2 < 8) {
    bVar2 = 0xfff < param_3;
  }
  if (4 < param_1) {
    bVar2 = true;
  }
  if (bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sdet_set_soft_vid]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sdet_set_soft_vid]input:sdet_no = %d,vln_id = %d,vln = %d\n",param_1,param_2,
           param_3,param_4);
  }
  if ((param_2 & 1) == 0) {
    cVar1 = tmOnuRegWrite(0xd,param_3,(param_2 >> 1) + param_1 * 4,&sdetgRegTable);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  else {
    cVar1 = tmOnuRegWrite(0xb,param_3,param_1 * 4 + (param_2 - 1 >> 1),&sdetgRegTable);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][sdet_set_soft_vid]write reg failed!\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

