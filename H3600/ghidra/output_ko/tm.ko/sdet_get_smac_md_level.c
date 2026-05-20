// module: tm.ko
// function: sdet_get_smac_md_level @ 0x36ca8
// size: 248 bytes
//

undefined4 sdet_get_smac_md_level(uint param_1,uint *param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint local_14;
  
  local_14 = 0;
  if (param_1 < 5) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sdet_get_smac_md_level]input:sdet_no = %d\n",param_1);
    }
    cVar1 = tmOnuRegRead(0xf,&local_14,param_1,&sdetgRegTable);
    if (cVar1 == '\0') {
      *param_2 = local_14 & 7;
      uVar2 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sdet_get_smac_md_level]input:md_level = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][sdet_get_smac_md_level] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][sdet_get_smac_md_level]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

