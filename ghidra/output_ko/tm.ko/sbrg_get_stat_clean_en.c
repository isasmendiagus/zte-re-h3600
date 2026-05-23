// module: tm.ko
// function: sbrg_get_stat_clean_en @ 0x187cc
// size: 160 bytes
//

undefined4 sbrg_get_stat_clean_en(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_c;
  
  local_c = 0;
  iVar1 = tmOnuRegRead(0xe,&local_c,0,&sbragRegTable);
  if (iVar1 == 0) {
    if (local_c < 2) {
      *param_1 = local_c;
    }
    if (g_tm_debug_level < 7) {
      uVar2 = 0;
    }
    else {
      printk("[TM][sbrg_get_stat_clean_en]output:clean_en = %d\n",*param_1);
      uVar2 = 0;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][sbrg_get_stat_clean_en] reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

