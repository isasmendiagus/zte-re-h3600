// module: tm.ko
// function: sdet_set_soft_vid_vld @ 0x36810
// size: 272 bytes
//

undefined4 sdet_set_soft_vid_vld(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = param_3 != 0;
  bVar2 = param_3 == 1;
  if (param_3 < 2) {
    bVar3 = 6 < param_2;
    bVar2 = param_2 == 7;
  }
  if (4 < param_1 || bVar3 && !bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sdet_set_soft_vid_vld]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sdet_set_soft_vid_vld]input:sdet_no = %d,vln_id = %d,vln = %d\n",param_1,param_2,
           param_3,param_4);
  }
  if ((param_2 & 1) == 0) {
    cVar1 = tmOnuRegWrite(0xc,param_3,(param_2 >> 1) + param_1 * 4,&sdetgRegTable);
  }
  else {
    cVar1 = tmOnuRegWrite(10,param_3,param_1 * 4 + (param_2 - 1 >> 1),&sdetgRegTable);
  }
  if (cVar1 != '\0') {
    if (g_tm_debug_level != 0) {
      printk("[TM][sdet_set_soft_vid_vld]write reg failed!\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  return 0;
}

