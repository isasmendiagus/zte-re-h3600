// module: tm.ko
// function: pon_pp_get_port_auth_en @ 0x287c8
// size: 292 bytes
//

int pon_pp_get_port_auth_en(uint *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_get_port_auth_en]intput: port_num=%d\n");
  }
  if (param_2 < 8) {
    iVar1 = tmOnuRegRead(5,local_1c,0,PonPpRegTable);
    if (iVar1 == 0) {
      *param_1 = local_1c[0] >> (param_2 & 0xff) & 1;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][pon_pp_get_port_auth_en]output: auth_en=%d\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7139,"pon_pp_get_port_auth_en"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x1da);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7136,"pon_pp_get_port_auth_en"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x1d3);
    }
    iVar1 = 1;
  }
  return iVar1;
}

