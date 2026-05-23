// module: tm.ko
// function: red_set_up_out_share_max @ 0x42d34
// size: 224 bytes
//

char red_set_up_out_share_max(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][red_set_all_out_share_max]input: up_out_max=%d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (0x7fff < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7207,"red_set_up_out_share_max"), iVar2 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_red.c",0x302);
    }
    return '\x01';
  }
  cVar1 = tmOnuRegWrite(0xc,param_1,0,RedRegTable);
  if (((cVar1 != '\0') && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7210,"red_set_up_out_share_max"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_red.c",0x30a);
  }
  return cVar1;
}

