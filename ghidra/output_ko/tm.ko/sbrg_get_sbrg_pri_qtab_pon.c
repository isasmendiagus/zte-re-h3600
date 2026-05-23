// module: tm.ko
// function: sbrg_get_sbrg_pri_qtab_pon @ 0x22e44
// size: 260 bytes
//

undefined4 sbrg_get_sbrg_pri_qtab_pon(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_1c [2];
  
  uVar1 = param_2;
  if (param_2 < 8) {
    uVar1 = param_1;
  }
  local_1c[0] = 0;
  if (uVar1 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_sbrg_pri_qtab_pon]input:port_id = %d,pri = %d\n",param_1,param_2);
    }
    iVar3 = tmOnuRegRead(param_1 + 0x50,local_1c,0,&sbragRegTable);
    if (iVar3 == 0) {
      *param_3 = local_1c[0] >> (param_2 * 3 & 0xff) & 3;
      uVar2 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_get_sbrg_pri_qtab_pon]output:en = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][sbrg_get_sbrg_pri_qtab_pon] reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][sbrg_get_sbrg_pri_qtab_pon]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

