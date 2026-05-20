// module: tm.ko
// function: sadm_set_indacs_dat @ 0x23d18
// size: 228 bytes
//

int sadm_set_indacs_dat(undefined4 param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][red_set_ind_acc_data]input:Index = %d,data = %d\n",param_2,param_1);
  }
  if (2 < param_2) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14335,"sadm_set_indacs_dat"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_sadm.c",0x28a);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(8,param_1,param_2,sadmRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_14338,"sadm_set_indacs_dat"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_sadm.c",0x292);
    return iVar1;
  }
  return iVar1;
}

