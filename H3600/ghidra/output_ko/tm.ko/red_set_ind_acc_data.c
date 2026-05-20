// module: tm.ko
// function: red_set_ind_acc_data @ 0x427cc
// size: 228 bytes
//

int red_set_ind_acc_data(undefined4 param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][red_set_ind_acc_data]input:Index = %d,data = %d\n",param_2,param_1);
  }
  if (3 < param_2) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7153,"red_set_ind_acc_data"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_red.c",0x211);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(6,param_1,param_2,RedRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7156,"red_set_ind_acc_data"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_red.c",0x219);
    return iVar1;
  }
  return iVar1;
}

