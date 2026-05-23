// module: tm.ko
// function: adm_get_up_drop_protocal_packtcnt @ 0x2bb00
// size: 292 bytes
//

int adm_get_up_drop_protocal_packtcnt(uint param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_get_up_drop_protocal_pktcnt]input: que_num=%d\n",param_1);
  }
  if (param_1 < 8) {
    iVar1 = tmOnuRegRead(0x13,&local_14,param_1,AdmRegTable);
    if (iVar1 == 0) {
      *param_2 = local_14;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][adm_get_up_drop_protocal_pktcnt]output: pkt_cnt=%d\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_7278,"adm_get_up_drop_protocal_packtcnt"), iVar2 == 0)) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x493);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7275,"adm_get_up_drop_protocal_packtcnt"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x48d);
    }
    iVar1 = 1;
  }
  return iVar1;
}

