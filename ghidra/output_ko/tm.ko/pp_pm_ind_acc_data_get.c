// module: tm.ko
// function: pp_pm_ind_acc_data_get @ 0x2cc84
// size: 256 bytes
//

int pp_pm_ind_acc_data_get(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  if (param_1 < 4) {
    iVar1 = tmOnuRegRead(2,local_14,param_1,&ppPmRegTable);
  }
  else {
    if (7 < param_1) {
      if (g_tm_debug_level != 0) {
        printk("[TM][pp_pm_ind_acc_data_get]input invalid parameter!\n");
        return 1;
      }
      return 1;
    }
    iVar1 = tmOnuRegRead(3,local_14,param_1 - 4,&ppPmRegTable);
  }
  if (iVar1 == 0) {
    *param_2 = local_14[0];
    if (g_tm_debug_level < 7) {
      return 0;
    }
    printk("[TM][pp_pm_ind_acc_data_get]output: data=%d\n");
  }
  else {
    if (g_tm_debug_level == 0) {
      return iVar1;
    }
    printk("[TM][pp_pm_ind_acc_data_get]read reg failed!\n");
  }
  return iVar1;
}

