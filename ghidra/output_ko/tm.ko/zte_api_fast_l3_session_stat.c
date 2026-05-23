// module: tm.ko
// function: zte_api_fast_l3_session_stat @ 0x63998
// size: 256 bytes
//

undefined4 zte_api_fast_l3_session_stat(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  *param_2 = 0;
  param_2[1] = 0;
  param_2[2] = 0;
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 0;
  param_2[7] = 0;
  param_2[8] = 0;
  param_2[9] = 0;
  param_2[10] = 0;
  param_2[0xb] = 0;
  iVar1 = adm_get_pkt_stastc(0,param_1,&local_28);
  if (iVar1 == 0) {
    param_2[3] = 0;
    param_2[7] = 0;
    param_2[2] = local_28;
    param_2[6] = local_24;
    iVar1 = adm_get_pkt_stastc(1,param_1,&local_20);
    if (iVar1 == 0) {
      param_2[1] = 0;
      param_2[5] = 0;
      *param_2 = local_20;
      param_2[4] = local_1c;
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("[%s]: read adm down stastc failed!\n","zte_sw_api.c");
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("[%s]: read adm up stastc failed!\n","zte_sw_api.c");
  }
  return 0xffffffff;
}

