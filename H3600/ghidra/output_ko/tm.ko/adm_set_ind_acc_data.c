// module: tm.ko
// function: adm_set_ind_acc_data @ 0x2acd4
// size: 232 bytes
//

int adm_set_ind_acc_data(uint param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_set_ind_acc_data]input: data_id = %d, data = 0x%x\n",param_1,param_2);
  }
  if (2 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7144,"adm_set_ind_acc_data"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x243);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(7,param_2,param_1,AdmRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7147,"adm_set_ind_acc_data"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp_adm.c",0x24b);
    return iVar1;
  }
  return iVar1;
}

