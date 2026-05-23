// module: tm.ko
// function: qmg_get_ddr_cache_enable @ 0x418f4
// size: 188 bytes
//

int qmg_get_ddr_cache_enable(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(3,local_14,0,QmgRegTable);
  if (iVar1 == 0) {
    if (local_14[0] < 2) {
      *param_1 = local_14[0];
    }
    if (g_tm_debug_level < 7) {
      iVar1 = 0;
    }
    else {
      printk("[TM][qmg_get_ddr_cache_enable]output: ddr_cache_en = %d\n",*param_1);
      iVar1 = 0;
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_6972,"qmg_get_ddr_cache_enable"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/tm_qmg.c",0x160);
  }
  return iVar1;
}

