// module: tm.ko
// function: pp_pm_ind_acc_done_get @ 0x2cb18
// size: 144 bytes
//

int pp_pm_ind_acc_done_get(uint *param_1)

{
  int iVar1;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(1,local_14,0,&ppPmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_ind_acc_done_get]output: access_done=%d\n");
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("[TM][pp_pm_ind_acc_done_get]read reg failed!\n");
  }
  return iVar1;
}

