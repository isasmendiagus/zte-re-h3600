// module: tm.ko
// function: sdet_get_soam_drop_en @ 0x36fe4
// size: 248 bytes
//

undefined4 sdet_get_soam_drop_en(uint param_1,uint *param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 < 6) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sdet_set_soam_drop_en]input:pro_pkt = %d\n",param_1);
    }
    cVar1 = tmOnuRegRead(0x11,local_1c,0,&sdetgRegTable);
    if (cVar1 == '\0') {
      *param_2 = local_1c[0] >> (param_1 & 0xff) & 1;
      uVar2 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sdet_set_soam_drop_en]input:action = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][sdet_set_soam_drop_en] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][sdet_set_soam_drop_en]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

