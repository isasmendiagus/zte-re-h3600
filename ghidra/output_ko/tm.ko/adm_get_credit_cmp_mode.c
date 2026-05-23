// module: tm.ko
// function: adm_get_credit_cmp_mode @ 0x2a660
// size: 188 bytes
//

int adm_get_credit_cmp_mode(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(1,local_14,0,AdmRegTable);
  if (iVar1 == 0) {
    if (local_14[0] < 2) {
      *param_1 = local_14[0];
    }
    if (g_tm_debug_level < 7) {
      iVar1 = 0;
    }
    else {
      printk("[TM][adm_get_credit_cmp_mode]output: mode = %d\n",*param_1);
      iVar1 = 0;
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7077,"adm_get_credit_cmp_mode"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x105);
  }
  return iVar1;
}

