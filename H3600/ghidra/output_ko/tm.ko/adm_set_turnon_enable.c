// module: tm.ko
// function: adm_set_turnon_enable @ 0x2a258
// size: 236 bytes
//

int adm_set_turnon_enable(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_set_turnon_enable]input: turnonen = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(&_rs_7041,"adm_set_turnon_enable"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x61);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0,param_1,0,AdmRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7044,"adm_set_turnon_enable"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp_adm.c",0x69);
    return iVar1;
  }
  return iVar1;
}

