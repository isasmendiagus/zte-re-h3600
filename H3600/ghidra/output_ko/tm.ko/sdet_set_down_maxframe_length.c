// module: tm.ko
// function: sdet_set_down_maxframe_length @ 0x36da0
// size: 180 bytes
//

undefined4
sdet_set_down_maxframe_length(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  if (0x3fff < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sdet_set_down_maxframe_length]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sdet_set_down_maxframe_length]input:len = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  cVar1 = tmOnuRegWrite(0x10,param_1,0,&sdetgRegTable);
  if (cVar1 == '\0') {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sdet_set_down_maxframe_length]write reg failed!\n");
  return 0xffffffff;
}

