// module: tm.ko
// function: sdet_get_soft_vid_vld @ 0x36920
// size: 328 bytes
//

undefined4 sdet_get_soft_vid_vld(uint param_1,uint param_2,uint *param_3)

{
  char cVar1;
  undefined4 uVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 < 5 && (param_2 < 8 && param_3 != (uint *)0x0)) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sdet_get_soft_vid_vld]input:sdet_no = %d,vln_id = %d\n",param_1,param_2);
    }
    if ((param_2 & 1) == 0) {
      cVar1 = tmOnuRegRead(0xd,local_1c,(param_2 >> 1) + param_1 * 4,&sdetgRegTable);
    }
    else {
      cVar1 = tmOnuRegRead(0xb,local_1c,param_1 * 4 + (param_2 - 1 >> 1),&sdetgRegTable);
    }
    if (cVar1 == '\0') {
      *param_3 = local_1c[0] & 1;
      uVar2 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sdet_get_soft_vid_vld]input:pvln = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][sdet_get_soft_vid_vld] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][sdet_get_soft_vid_vld]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

