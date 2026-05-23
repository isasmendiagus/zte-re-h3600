// module: tm.ko
// function: pon_pp_set_mult_mode @ 0x28d48
// size: 240 bytes
//

undefined4 pon_pp_set_mult_mode(uint param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_mult_mode]input: dir=%d,mult_mode=%d\n",param_2,param_1);
  }
  bVar4 = 1 < param_1;
  bVar3 = param_1 == 2;
  if (param_1 < 3) {
    bVar4 = param_2 != 0;
    bVar3 = param_2 == 1;
  }
  if (!bVar4 || bVar3) {
    if (param_2 == 0) {
      uVar1 = 8;
    }
    else {
      uVar1 = 9;
    }
    iVar2 = tmOnuRegWrite(uVar1,param_1,0,PonPpRegTable);
    if (iVar2 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_7193,"pon_pp_set_mult_mode"), iVar2 != 0)) {
        printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x301);
      }
      return 0xffffffff;
    }
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar2 = ___ratelimit(_rs_7190,"pon_pp_set_mult_mode"), iVar2 != 0)
     ) {
    printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x2f1);
  }
  return 1;
}

