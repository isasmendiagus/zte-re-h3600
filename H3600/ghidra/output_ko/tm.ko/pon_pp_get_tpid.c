// module: tm.ko
// function: pon_pp_get_tpid @ 0x29d5c
// size: 288 bytes
//

int pon_pp_get_tpid(uint *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_get_tpid]intput: tpid_num=%d\n");
  }
  if (param_2 < 8) {
    iVar1 = tmOnuRegRead(0x11,&local_14,param_2,PonPpRegTable);
    if (iVar1 == 0) {
      *param_1 = local_14 & 0xffff;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][pon_pp_get_tpid]output: tpid_val=%d\n");
    }
    else {
      if ((g_tm_debug_level == 0) || (iVar2 = ___ratelimit(_rs_7367,"pon_pp_get_tpid"), iVar2 == 0))
      {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x593);
    }
  }
  else {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7364,"pon_pp_get_tpid"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x58c);
    }
    iVar1 = 1;
  }
  return iVar1;
}

