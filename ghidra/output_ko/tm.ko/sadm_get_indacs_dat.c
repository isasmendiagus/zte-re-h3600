// module: tm.ko
// function: sadm_get_indacs_dat @ 0x23e0c
// size: 288 bytes
//

int sadm_get_indacs_dat(undefined4 *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][red_get_ind_acc_data]input:Index = %d\n");
  }
  if (param_2 < 3) {
    iVar1 = tmOnuRegRead(8,&local_14,param_2,sadmRegTable);
    if (iVar1 == 0) {
      *param_1 = local_14;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][red_get_ind_acc_data]output:data = %d\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_14349,"sadm_get_indacs_dat"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_sadm.c",700);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14346,"sadm_get_indacs_dat"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_sadm.c",0x2b4);
    }
    iVar1 = 1;
  }
  return iVar1;
}

