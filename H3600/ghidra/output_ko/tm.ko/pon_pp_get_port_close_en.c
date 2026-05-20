// module: tm.ko
// function: pon_pp_get_port_close_en @ 0x28a70
// size: 292 bytes
//

int pon_pp_get_port_close_en(uint *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_get_port_close_en]intput: port_num=%d\n");
  }
  if (param_2 < 8) {
    iVar1 = tmOnuRegRead(6,local_1c,0,PonPpRegTable);
    if (iVar1 == 0) {
      *param_1 = local_1c[0] >> (param_2 & 0xff) & 1;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][pon_pp_get_port_close_en]output: close_en=%d\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7164,"pon_pp_get_port_close_en"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x236);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7161,"pon_pp_get_port_close_en"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x22f);
    }
    iVar1 = 1;
  }
  return iVar1;
}

