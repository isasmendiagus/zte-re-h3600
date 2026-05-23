// module: tm.ko
// function: adm_set_one_second @ 0x2b2e0
// size: 224 bytes
//

int adm_set_one_second(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_set_one_second]input:  vlaue=%d\n",param_1,param_3,g_tm_debug_level,param_4);
  }
  if (0xfffffff < param_1) {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7195,"adm_set_one_second"), iVar1 != 0)
       ) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x34c);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0xb,param_1,0,AdmRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7198,"adm_set_one_second"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp_adm.c",0x354);
    return iVar1;
  }
  return iVar1;
}

