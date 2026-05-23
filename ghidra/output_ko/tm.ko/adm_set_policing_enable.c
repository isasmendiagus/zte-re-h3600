// module: tm.ko
// function: adm_set_policing_enable @ 0x2b3d0
// size: 264 bytes
//

int adm_set_policing_enable(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_set_policing_enable]input: que_num=%d, polic_en=%d\n");
  }
  uVar1 = param_1;
  if (param_1 < 2) {
    uVar1 = param_3;
  }
  if (7 < param_2 || 1 < uVar1) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7207,"adm_set_policing_enable"), iVar2 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x376);
    }
    return 1;
  }
  if (param_1 == 0) {
    uVar3 = 0xd;
  }
  else {
    uVar3 = 0xc;
  }
  iVar2 = tmOnuRegWrite(uVar3,param_3,param_2,AdmRegTable,param_4);
  if (((iVar2 != 0) && (g_tm_debug_level != 0)) &&
     (iVar4 = ___ratelimit(_rs_7210,"adm_set_policing_enable"), iVar4 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp_adm.c",0x387);
    return iVar2;
  }
  return iVar2;
}

