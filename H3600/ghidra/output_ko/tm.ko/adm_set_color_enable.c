// module: tm.ko
// function: adm_set_color_enable @ 0x2a418
// size: 188 bytes
//

int adm_set_color_enable(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_set_color_enable]input: colorEn = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x9e,g_tm_debug_level,param_4);
    return 1;
  }
  iVar1 = tmOnuRegWrite(2,param_1,0,AdmRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp_adm.c",0xa6,g_tm_debug_level,param_4);
    return iVar1;
  }
  return iVar1;
}

