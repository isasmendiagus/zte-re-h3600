// module: tm.ko
// function: sbrg_get_dft_unkuni_vl_trans_pktdeal @ 0x21aec
// size: 248 bytes
//

undefined4 sbrg_get_dft_unkuni_vl_trans_pktdeal(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_dft_unkuni_vl_trans_pktdeal]input:port_id = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(0x45,local_1c,0,&sbragRegTable);
    if (iVar2 == 0) {
      *param_2 = local_1c[0] >> ((param_1 & 0x7f) << 1) & 3;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_get_dft_unkuni_vl_trans_pktdeal]output:pktdeal = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][sbrg_get_dft_unkuni_vl_trans_pktdeal] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_get_dft_unkuni_vl_trans_pktdeal]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

