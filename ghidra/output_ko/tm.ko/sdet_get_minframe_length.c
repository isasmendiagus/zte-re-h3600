// module: tm.ko
// function: sdet_get_minframe_length @ 0x35e04
// size: 156 bytes
//

undefined4 sdet_get_minframe_length(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  cVar1 = tmOnuRegRead(5,local_14,0,&sdetgRegTable);
  if (cVar1 == '\0') {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sdet_get_minframe_length]output:len = %d\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][sdet_get_minframe_length] reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

