// module: tm.ko
// function: sbrg_set_sbrg_pri_qtab_pon @ 0x22d14
// size: 304 bytes
//

undefined4 sbrg_set_sbrg_pri_qtab_pon(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_1c [2];
  
  uVar1 = param_3;
  if (param_3 < 8) {
    uVar1 = param_2;
  }
  if (param_1 < 8 && uVar1 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_set_sbrg_pri_qtab_pon]input:port_id = %d,pri = %d,value=%d\n",param_1,
             param_2,param_3);
    }
    iVar2 = tmOnuRegRead(param_1 + 0x50,local_1c,0,&sbragRegTable);
    if (iVar2 == 0) {
      iVar2 = tmOnuRegWrite(param_1 + 0x50,
                            local_1c[0] & ~(7 << (param_2 * 3 & 0xff)) |
                            param_3 << (param_2 * 3 & 0xff),0,&sbragRegTable);
      uVar3 = 0;
      if (iVar2 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][sbrg_set_sbrg_pri_qtab_pon]write reg failed!\n");
        return 0xffffffff;
      }
    }
    else {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_set_sbrg_pri_qtab_pon] reg read failed\n");
      uVar3 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar3 = 1;
  }
  else {
    printk("[TM][sbrg_set_sbrg_pri_qtab_pon]input invalid parameter!\n");
    uVar3 = 1;
  }
  return uVar3;
}

