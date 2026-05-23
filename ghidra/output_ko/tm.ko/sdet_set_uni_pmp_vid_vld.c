// module: tm.ko
// function: sdet_set_uni_pmp_vid_vld @ 0x35ea0
// size: 192 bytes
//

undefined4 sdet_set_uni_pmp_vid_vld(uint param_1,uint param_2)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = param_2 != 0;
  bVar2 = param_2 == 1;
  if (param_2 < 2) {
    bVar3 = 3 < param_1;
    bVar2 = param_1 == 4;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sdet_set_uni_pmp_vid_vld]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sdet_set_uni_pmp_vid_vld]input:sdet_no = %d,vln1 = %d\n",param_1,param_2);
  }
  cVar1 = tmOnuRegWrite(6,param_2,param_1,&sdetgRegTable);
  if (cVar1 == '\0') {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sdet_set_uni_pmp_vid_vld]write reg failed!\n");
  return 0xffffffff;
}

