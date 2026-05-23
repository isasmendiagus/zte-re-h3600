// module: tm.ko
// function: pon_pp_get_dslite_traffclass_hoplimit @ 0x2a144
// size: 272 bytes
//

int pon_pp_get_dslite_traffclass_hoplimit(uint param_1,uint *param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_get_dslite_traffclass_hoplimit]input: num = %d\n",param_1);
  }
  if (param_1 < 8) {
    iVar1 = tmOnuRegRead(0x13,local_1c,param_1,PonPpRegTable);
    if (iVar1 == 0) {
      uVar2 = (local_1c[0] << 0x10) >> 0x18;
      *param_3 = local_1c[0] & 0xff;
      *param_2 = uVar2;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][pon_pp_get_dslite_traffclass_hoplimit]output: traffic_class = %d, hoplimit = %d\n"
             ,uVar2,*param_3);
    }
    else {
      if (g_tm_debug_level == 0) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_reg.c",0x62d);
    }
  }
  else if (g_tm_debug_level == 0) {
    iVar1 = 1;
  }
  else {
    printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x626);
    iVar1 = 1;
  }
  return iVar1;
}

