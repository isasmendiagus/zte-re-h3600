// module: tm.ko
// function: adm_get_pass_pktcnt_persec @ 0x2b754
// size: 308 bytes
//

int adm_get_pass_pktcnt_persec(uint param_1,uint param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  undefined4 local_1c [2];
  
  local_1c[0] = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_get_pass_pktcnt_persec]input: que_num=%d\n");
  }
  bVar5 = param_1 != 0;
  bVar4 = param_1 == 1;
  if (param_1 < 2) {
    bVar5 = 6 < param_2;
    bVar4 = param_2 == 7;
  }
  if (!bVar5 || bVar4) {
    if (param_1 == 0) {
      uVar2 = 0xf;
    }
    else {
      uVar2 = 0xe;
    }
    iVar1 = tmOnuRegRead(uVar2,local_1c,param_2,AdmRegTable);
    if (iVar1 == 0) {
      *param_3 = local_1c[0];
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][adm_get_pass_pktcnt_persec]output: pkt_cnt=%d\n");
    }
    else {
      if (g_tm_debug_level == 0) {
        return iVar1;
      }
      iVar3 = ___ratelimit(_rs_7245,"adm_get_pass_pktcnt_persec");
      if (iVar3 == 0) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x41c);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7242,"adm_get_pass_pktcnt_persec"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x40d);
    }
    iVar1 = 1;
  }
  return iVar1;
}

