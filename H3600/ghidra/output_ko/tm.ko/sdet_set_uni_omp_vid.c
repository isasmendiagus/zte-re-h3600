// module: tm.ko
// function: sdet_set_uni_omp_vid @ 0x363ec
// size: 192 bytes
//

undefined4 sdet_set_uni_omp_vid(uint param_1,uint param_2)

{
  char cVar1;
  bool bVar2;
  
  bVar2 = 3 < param_1;
  if (param_1 < 5) {
    bVar2 = 0xfff < param_2;
  }
  if (bVar2) {
    if (g_tm_debug_level < 7) {
      return 1;
    }
    printk("[TM][sdet_set_uni_omp_vid]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sdet_set_uni_omp_vid]input:sdet_no = %d,vln2 = %d\n",param_1,param_2);
  }
  cVar1 = tmOnuRegWrite(9,param_2,param_1,&sdetgRegTable);
  if (cVar1 == '\0') {
    return 0;
  }
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][sdet_set_uni_omp_vid]write reg failed!\n");
  return 0xffffffff;
}

