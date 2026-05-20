// module: tm.ko
// function: sdet_get_maxframe_length @ 0x35c60
// size: 240 bytes
//

undefined4 sdet_get_maxframe_length(uint param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_1 < 5) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sdet_set_maxframe_length]input:sdet_no = %d\n",param_1);
    }
    cVar1 = tmOnuRegRead(param_1,&local_14,0,&sdetgRegTable);
    if (cVar1 == '\0') {
      *param_2 = local_14;
      uVar2 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sdet_get_maxframe_length]output:len = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][sdet_get_maxframe_length] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][sdet_get_maxframe_length]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

