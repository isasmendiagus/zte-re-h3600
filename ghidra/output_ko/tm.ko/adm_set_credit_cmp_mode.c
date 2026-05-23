// module: tm.ko
// function: adm_set_credit_cmp_mode @ 0x2a570
// size: 224 bytes
//

int adm_set_credit_cmp_mode(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_set_credit_cmp_mode]input: mode = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7067,"adm_set_credit_cmp_mode"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0xdc);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(1,param_1,0,AdmRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7070,"adm_set_credit_cmp_mode"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp_adm.c",0xe4);
    return iVar1;
  }
  return iVar1;
}

