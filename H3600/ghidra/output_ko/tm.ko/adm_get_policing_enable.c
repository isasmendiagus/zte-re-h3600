// module: tm.ko
// function: adm_get_policing_enable @ 0x2b4e8
// size: 324 bytes
//

int adm_get_policing_enable(uint param_1,uint param_2,uint *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_get_policing_enable]input: que_num=%d\n");
  }
  bVar5 = param_1 != 0;
  bVar4 = param_1 == 1;
  if (param_1 < 2) {
    bVar5 = 6 < param_2;
    bVar4 = param_2 == 7;
  }
  if (!bVar5 || bVar4) {
    if (param_1 == 0) {
      uVar2 = 0xd;
    }
    else {
      uVar2 = 0xc;
    }
    iVar1 = tmOnuRegRead(uVar2,local_1c,param_2,AdmRegTable);
    if (iVar1 == 0) {
      if (local_1c[0] < 2) {
        *param_3 = local_1c[0];
      }
      if (g_tm_debug_level < 7) {
        iVar1 = 0;
      }
      else {
        printk("[TM][adm_get_policing_enable]output: polic_en=%d\n",*param_3);
        iVar1 = 0;
      }
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar3 = ___ratelimit(_rs_7222,"adm_get_policing_enable"), iVar3 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x3b7);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7219,"adm_get_policing_enable"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x3a9);
    }
    iVar1 = 1;
  }
  return iVar1;
}

