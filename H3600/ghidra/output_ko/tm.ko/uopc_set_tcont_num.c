// module: tm.ko
// function: uopc_set_tcont_num @ 0x3bf70
// size: 348 bytes
//

int uopc_set_tcont_num(uint param_1)

{
  int iVar1;
  int local_14;
  
  local_14 = 1;
  if (6 < g_tm_debug_level) {
    printk("[TM][uopc_set_tcont_num]input:tcont_num = %d\n",param_1);
  }
  if (param_1 - 1 < 7) {
    iVar1 = tmOnuRegRead(0,&local_14,0,&UopcRegTable);
    if (iVar1 == 0) {
      if (local_14 == 0) {
        iVar1 = tmOnuRegWrite(1,param_1 | 8,0,&UopcRegTable);
        if (iVar1 == 0) {
          return 0;
        }
        if (g_tm_debug_level == 0) {
          return iVar1;
        }
        printk("ERROR:(%s:%d) reg write fail\n","npp/pon_npp_uopc.c",0x59);
      }
      else if (g_tm_debug_level == 0) {
        iVar1 = -1;
      }
      else {
        printk("ERROR:(%s:%d) tcont num request invalid\n","npp/pon_npp_uopc.c",0x60);
        iVar1 = -1;
      }
    }
    else {
      if (g_tm_debug_level == 0) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","npp/pon_npp_uopc.c",0x50);
    }
  }
  else if (g_tm_debug_level == 0) {
    iVar1 = 1;
  }
  else {
    printk("ERROR:(%s:%d) input invalid parameter!\n\n","npp/pon_npp_uopc.c",0x49);
    iVar1 = 1;
  }
  return iVar1;
}

