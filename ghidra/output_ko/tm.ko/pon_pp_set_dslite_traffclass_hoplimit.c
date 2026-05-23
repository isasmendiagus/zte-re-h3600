// module: tm.ko
// function: pon_pp_set_dslite_traffclass_hoplimit @ 0x2a05c
// size: 228 bytes
//

int pon_pp_set_dslite_traffclass_hoplimit(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_dslite_traffclass_hoplimit]input: num = %d, traffic_class = %d, hoplimit = %d\n"
           ,param_1,param_2,param_3,param_4);
  }
  uVar1 = param_3;
  if (param_3 < 0x100) {
    uVar1 = param_2;
  }
  if (param_1 < 8 && uVar1 < 0x100) {
    iVar2 = tmOnuRegWrite(0x13,param_3 | param_2 << 8,param_1,PonPpRegTable);
    if ((iVar2 != 0) && (g_tm_debug_level != 0)) {
      printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x608,g_tm_debug_level,param_4);
      return iVar2;
    }
    return iVar2;
  }
  if (g_tm_debug_level != 0) {
    printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x5ff,g_tm_debug_level,param_4);
    return 1;
  }
  return 1;
}

