// module: tm.ko
// function: red_get_ind_acc_data @ 0x428c0
// size: 288 bytes
//

int red_get_ind_acc_data(undefined4 *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][red_get_ind_acc_data]input:Index = %d\n");
  }
  if (param_2 < 4) {
    iVar1 = tmOnuRegRead(6,&local_14,param_2,RedRegTable);
    if (iVar1 == 0) {
      *param_1 = local_14;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][red_get_ind_acc_data]output:data = %d\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7167,"red_get_ind_acc_data"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_red.c",0x243);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7164,"red_get_ind_acc_data"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_red.c",0x23b);
    }
    iVar1 = 1;
  }
  return iVar1;
}

