// module: tm.ko
// function: pp_pm_cfg_padding_en_get @ 0x2ce2c
// size: 112 bytes
//

int pp_pm_cfg_padding_en_get
              (undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = tmOnuRegRead(5,param_1,0,&ppPmRegTable,param_4);
  if (iVar1 == 0) {
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_cfg_padding_en_get]output: pad_en=%d\n",*param_1);
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("[TM][pp_pm_cfg_padding_en_get]read reg failed!\n");
  }
  return iVar1;
}

