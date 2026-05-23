// module: tm.ko
// function: pon_pp_get_mult_mode @ 0x28e48
// size: 304 bytes
//

int pon_pp_get_mult_mode(uint *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_get_mult_mode]intput: dir=%d\n");
  }
  if (param_2 == 0) {
    uVar3 = 8;
  }
  else {
    if (param_2 != 1) {
      if ((g_tm_debug_level != 0) &&
         (iVar1 = ___ratelimit(_rs_7202,"pon_pp_get_mult_mode"), iVar1 != 0)) {
        printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x32a);
      }
      return 1;
    }
    uVar3 = 9;
  }
  iVar1 = tmOnuRegRead(uVar3,&local_14,0,PonPpRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14 & 3;
    if (g_tm_debug_level < 7) {
      return 0;
    }
    printk("[TM][pon_pp_get_mult_mode]output: mult_mode=%d\n");
  }
  else {
    if ((g_tm_debug_level == 0) ||
       (iVar2 = ___ratelimit(_rs_7205,"pon_pp_get_mult_mode"), iVar2 == 0)) {
      return iVar1;
    }
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x331);
  }
  return iVar1;
}

