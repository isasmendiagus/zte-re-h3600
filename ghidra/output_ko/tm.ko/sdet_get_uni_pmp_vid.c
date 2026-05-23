// module: tm.ko
// function: sdet_get_uni_pmp_vid @ 0x36124
// size: 260 bytes
//

uint sdet_get_uni_pmp_vid(uint param_1,undefined4 *param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_1 < 5 && param_2 != (undefined4 *)0x0) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sdet_get_uni_pmp_vid]input:sdet_no = %d\n",param_1);
    }
    cVar1 = tmOnuRegRead(7,&local_14,param_1,&sdetgRegTable);
    if (cVar1 == '\0') {
      *param_2 = local_14;
      uVar2 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sdet_get_uni_pmp_vid]output:pvln1 = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][sdet_get_uni_pmp_vid] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    uVar2 = (uint)(g_tm_debug_level < 7);
    if (6 < g_tm_debug_level) {
      printk("[TM][sdet_get_uni_pmp_vid]input invalid parameter!\n");
      uVar2 = 1;
    }
  }
  return uVar2;
}

