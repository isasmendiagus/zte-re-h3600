// module: tm.ko
// function: adm_get_turnon_enable @ 0x2a34c
// size: 192 bytes
//

int adm_get_turnon_enable(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0,local_14,0,AdmRegTable);
  if (iVar1 == 0) {
    if (local_14[0] < 2) {
      *param_1 = local_14[0];
    }
    if (g_tm_debug_level < 7) {
      iVar1 = 0;
    }
    else {
      printk("[TM][adm_get_TurnOn_Enable]output: TurnOnEn = %d\n",*param_1);
      iVar1 = 0;
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7051,"adm_get_turnon_enable"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x8b);
  }
  return iVar1;
}

