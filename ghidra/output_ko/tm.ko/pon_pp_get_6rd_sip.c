// module: tm.ko
// function: pon_pp_get_6rd_sip @ 0x27ad8
// size: 404 bytes
//

int pon_pp_get_6rd_sip(uint param_1,undefined1 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if ((6 < g_tm_debug_level) && (iVar1 = ___ratelimit(&_rs_7417,"pon_pp_get_6rd_sip"), iVar1 != 0))
  {
    printk("[TM][pon_pp_set_6rd_sip]input: addr_sel = %d\n",param_1);
  }
  if (param_1 < 8) {
    iVar1 = tmOnuRegRead(0x14,&local_14,param_1,PonPpRegTable);
    if (iVar1 == 0) {
      param_2[3] = (char)local_14;
      *param_2 = (char)((uint)local_14 >> 0x18);
      param_2[1] = (char)((uint)local_14 >> 0x10);
      param_2[2] = (char)((uint)local_14 >> 8);
      if ((g_tm_debug_level < 7) ||
         (iVar2 = ___ratelimit(_rs_7424,"pon_pp_get_6rd_sip"), iVar2 == 0)) {
        return 0;
      }
      printk("[TM][pon_pp_set_6rd_sip]output: sip_6rd = %d.%d.%d.%d\n",*param_2,param_2[1],
             param_2[2],param_2[3]);
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7422,"pon_pp_get_6rd_sip"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_reg.c",0x67c);
    }
  }
  else {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7420,"pon_pp_get_6rd_sip"), iVar1 != 0)
       ) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x675);
    }
    iVar1 = 1;
  }
  return iVar1;
}

