// module: tm.ko
// function: sch_set_hw_age_time @ 0x3d388
// size: 132 bytes
//

undefined4
sch_set_hw_age_time(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][sch_set_hw_age_time]input:ageTime = %d\n",param_1,param_3,g_tm_debug_level,param_4)
    ;
  }
  iVar1 = tmOnuRegWrite(10,param_1,0,&SchRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_sch.c",0x2fe,g_tm_debug_level,param_4);
  return 0xffffffff;
}

