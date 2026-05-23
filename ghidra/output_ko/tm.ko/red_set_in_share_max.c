// module: tm.ko
// function: red_set_in_share_max @ 0x429f0
// size: 220 bytes
//

int red_set_in_share_max(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][red_set_in_share_max]input:share_max = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (0x1fff < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7173,"red_set_in_share_max"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_red.c",0x267);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(7,param_1,0,RedRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7176,"red_set_in_share_max"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_red.c",0x26f);
  }
  return iVar1;
}

