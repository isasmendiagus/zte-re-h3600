// module: tm.ko
// function: adm_set_pass_pktcnt_persec @ 0x2b63c
// size: 264 bytes
//

int adm_set_pass_pktcnt_persec(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_set_pass_pktcnt_persec]input: que_num=%d, pkt_cnt=%d\n");
  }
  bVar4 = param_1 != 0;
  if (param_1 < 2) {
    bVar4 = 0x1fffff < param_3;
  }
  if (7 < param_2) {
    bVar4 = true;
  }
  if (bVar4) {
    if ((g_tm_debug_level != 0) &&
       (iVar2 = ___ratelimit(_rs_7230,"adm_set_pass_pktcnt_persec"), iVar2 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x3dc);
    }
    return 1;
  }
  if (param_1 == 0) {
    uVar1 = 0xf;
  }
  else {
    uVar1 = 0xe;
  }
  iVar2 = tmOnuRegWrite(uVar1,param_3,param_2,AdmRegTable,param_4);
  if (((iVar2 != 0) && (g_tm_debug_level != 0)) &&
     (iVar3 = ___ratelimit(_rs_7233,"adm_set_pass_pktcnt_persec"), iVar3 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp_adm.c",0x3eb);
    return iVar2;
  }
  return iVar2;
}

