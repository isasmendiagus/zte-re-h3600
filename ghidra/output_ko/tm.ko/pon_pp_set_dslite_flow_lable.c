// module: tm.ko
// function: pon_pp_set_dslite_flow_lable @ 0x29e8c
// size: 200 bytes
//

int pon_pp_set_dslite_flow_lable(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_dslite_flow_lable]input: num=%d, flow_lable=%x\n",param_1,param_2);
  }
  bVar2 = 6 < param_1;
  if (param_1 < 8) {
    bVar2 = 0xfffff < param_2;
  }
  if (bVar2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x5b2);
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x12,param_2,param_1,PonPpRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x5ba);
    return iVar1;
  }
  return iVar1;
}

