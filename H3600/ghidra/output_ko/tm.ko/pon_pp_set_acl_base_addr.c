// module: tm.ko
// function: pon_pp_set_acl_base_addr @ 0x2991c
// size: 144 bytes
//

undefined4
pon_pp_set_acl_base_addr
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_acl_base_addr]input: base_addr=%d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  iVar1 = tmOnuRegWrite(0xf,param_1,0,PonPpRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_7317,"pon_pp_set_acl_base_addr"), iVar1 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x4dc);
  }
  return 0xffffffff;
}

