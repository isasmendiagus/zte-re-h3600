// module: tm.ko
// function: sdet_get_c_tpid @ 0x36b1c
// size: 204 bytes
//

undefined4 sdet_get_c_tpid(uint *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  if (param_1 == (uint *)0x0) {
    if (g_tm_debug_level == 0) {
      uVar2 = 1;
    }
    else {
      printk("[TM][sdet_get_c_tpid]input invalid parameter!\n");
      uVar2 = 1;
    }
  }
  else {
    cVar1 = tmOnuRegRead(0xe,local_14,0,&sdetgRegTable);
    if (cVar1 == '\0') {
      *param_1 = local_14[0] & 0xffff;
      uVar2 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sdet_get_c_tpid]output:c_tpid = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][sdet_get_c_tpid] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

