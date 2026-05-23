// module: tm.ko
// function: red_set_trap_color_en @ 0x42208
// size: 220 bytes
//

undefined4
red_set_trap_color_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][red_set_trap_color_en]input: trap_color_en = %d\n",param_1,param_3,g_tm_debug_level
           ,param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7095,"red_set_trap_color_en"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) input invalid parameter!\n\n","tm/src/pon_tm_red.c",0xf5);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(2,param_1,0,RedRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_7098,"red_set_trap_color_en"), iVar1 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_red.c",0xff);
  }
  return 0xffffffff;
}

