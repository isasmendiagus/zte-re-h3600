// module: tm.ko
// function: pon_pp_set_tpid @ 0x29c68
// size: 228 bytes
//

undefined4 pon_pp_set_tpid(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_tpid]input: tpid_num=%d,tpid_val=%d\n",param_2,param_1);
  }
  bVar2 = 6 < param_2;
  if (param_2 < 8) {
    bVar2 = 0xffff < param_1;
  }
  if (bVar2) {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7353,"pon_pp_set_tpid"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x565);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x11,param_1,param_2,PonPpRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7356,"pon_pp_set_tpid"), iVar1 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x56c);
  }
  return 0xffffffff;
}

