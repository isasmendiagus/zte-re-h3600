// module: tm.ko
// function: pp_pm_ind_acc_data_set @ 0x2cba8
// size: 220 bytes
//

int pp_pm_ind_acc_data_set(uint param_1,undefined4 param_2)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pp_pm_ind_acc_data_set]input: data_id = %d, data = %d\n",param_1,param_2);
  }
  if (param_1 < 4) {
    iVar1 = tmOnuRegWrite(2,param_2,param_1,&ppPmRegTable);
  }
  else {
    if (7 < param_1) {
      if (g_tm_debug_level == 0) {
        return 1;
      }
      printk("[TM][pp_pm_ind_acc_data_set]input invalid parameter!\n");
      return 1;
    }
    iVar1 = tmOnuRegWrite(3,param_2,param_1 - 4,&ppPmRegTable);
  }
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("[TM][pp_pm_ind_acc_data_set]write reg failed!\n");
    return iVar1;
  }
  return iVar1;
}

