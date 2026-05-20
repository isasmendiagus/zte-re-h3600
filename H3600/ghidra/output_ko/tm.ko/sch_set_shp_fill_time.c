// module: tm.ko
// function: sch_set_shp_fill_time @ 0x3db28
// size: 236 bytes
//

int sch_set_shp_fill_time(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][sch_set_shp_fill_time]input:fillTime = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (0x1ffff < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7318,"sch_set_shp_fill_time"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_sch.c",0x480);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x11,param_1,0,&SchRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7321,"sch_set_shp_fill_time"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_sch.c",0x488);
    return iVar1;
  }
  return iVar1;
}

