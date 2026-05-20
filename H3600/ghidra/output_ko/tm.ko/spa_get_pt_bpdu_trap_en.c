// module: tm.ko
// function: spa_get_pt_bpdu_trap_en @ 0x38b94
// size: 248 bytes
//

undefined4 spa_get_pt_bpdu_trap_en(int param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 - 1U < 7) {
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_get_pt_bpdu_trap_en]input:port_id = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(8,local_1c,0,&spaRegTable);
    if (iVar2 == 0) {
      *param_2 = local_1c[0] >> (param_1 - 1U & 0xff) & 1;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][spa_get_pt_bpdu_trap_en]output:trap_en = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][spa_get_pt_bpdu_trap_en]read reg failed!\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][spa_get_pt_bpdu_trap_en]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

