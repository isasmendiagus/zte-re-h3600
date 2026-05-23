// module: tm.ko
// function: pp_pm_cfg_padding_en_set @ 0x2cd84
// size: 168 bytes
//

int pp_pm_cfg_padding_en_set(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_cfg_padding_en_set]input: pad_en=%d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][pp_pm_cfg_padding_en_set]input invalid parameter!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(5,param_1,0,&ppPmRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][pp_pm_cfg_padding_en_set]write reg failed!\n");
    return iVar1;
  }
  return iVar1;
}

