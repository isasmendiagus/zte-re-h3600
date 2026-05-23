// module: tm.ko
// function: adm_get_ind_acc_data @ 0x2adcc
// size: 292 bytes
//

int adm_get_ind_acc_data(uint param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_get_ind_acc_data]input: data_id = %d\n",param_1);
  }
  if (param_1 < 3) {
    iVar1 = tmOnuRegRead(7,&local_14,param_1,AdmRegTable);
    if (iVar1 == 0) {
      *param_2 = local_14;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][adm_get_ind_acc_data]output: data = 0x%x\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7158,"adm_get_ind_acc_data"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x274);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7155,"adm_get_ind_acc_data"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x26c);
    }
    iVar1 = 1;
  }
  return iVar1;
}

