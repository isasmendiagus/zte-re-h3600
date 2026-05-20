// module: tm.ko
// function: zte_api_set_6rd_sip @ 0x63a98
// size: 4 bytes
//

int zte_api_set_6rd_sip(uint param_1,byte *param_2)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_6rd_sip]input: addr_sel= %d, sip_6rd = %d.%d.%d.%d\n",param_1,*param_2,
           param_2[1],param_2[2],param_2[3]);
  }
  if (param_1 < 0x10) {
    iVar1 = tmOnuRegWrite(0x14,(uint)param_2[1] << 0x10 | (uint)*param_2 << 0x18 | (uint)param_2[3]
                               | (uint)param_2[2] << 8,param_1,PonPpRegTable);
    if (((iVar1 == 0) || (g_tm_debug_level == 0)) ||
       (iVar2 = ___ratelimit(_rs_7403,"pon_pp_set_6rd_sip"), iVar2 == 0)) {
      return iVar1;
    }
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x658);
  }
  else {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7400,"pon_pp_set_6rd_sip"), iVar1 != 0)
       ) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x64f);
    }
    iVar1 = 1;
  }
  return iVar1;
}

