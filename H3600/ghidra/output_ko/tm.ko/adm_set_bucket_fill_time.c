// module: tm.ko
// function: adm_set_bucket_fill_time @ 0x2a8cc
// size: 224 bytes
//

int adm_set_bucket_fill_time(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_set_bucket_fill_time]input: time_val = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (0x3ffff < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7101,"adm_set_bucket_fill_time"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x176);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(4,param_1,0,AdmRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7104,"adm_set_bucket_fill_time"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp_adm.c",0x17e);
    return iVar1;
  }
  return iVar1;
}

