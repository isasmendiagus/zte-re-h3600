// module: tm.ko
// function: sdet_set_maxframe_length @ 0x35ba0
// size: 192 bytes
//

undefined4 sdet_set_maxframe_length(uint param_1,uint param_2)

{
  char cVar1;
  bool bVar2;
  
  bVar2 = 3 < param_1;
  if (param_1 < 5) {
    bVar2 = 0x3fff < param_2;
  }
  if (bVar2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sdet_set_maxframe_length]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sdet_set_maxframe_length]input:sdet_no = %d,len = %d\n",param_1,param_2);
  }
  cVar1 = tmOnuRegWrite(param_1,param_2,0,&sdetgRegTable);
  if (cVar1 == '\0') {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sdet_set_maxframe_length]write reg failed!\n");
  return 0xffffffff;
}

