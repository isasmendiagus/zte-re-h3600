// module: tm.ko
// function: red_set_share_mode @ 0x423b4
// size: 220 bytes
//

undefined4 red_set_share_mode(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][red_set_share_mode]input: mode = %d\n",param_1,param_3,g_tm_debug_level,param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7113,"red_set_share_mode"), iVar1 != 0)
       ) {
      printk("ERROR:(%s:%d) input invalid parameter!\n\n","tm/src/pon_tm_red.c",0x145);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(3,param_1,0,RedRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7116,"red_set_share_mode"), iVar1 != 0))
  {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_red.c",0x14f);
  }
  return 0xffffffff;
}

