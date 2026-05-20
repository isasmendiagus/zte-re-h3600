// module: tm.ko
// function: spa_get_indirect_rw_data @ 0x38038
// size: 232 bytes
//

undefined4 spa_get_indirect_rw_data(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][spa_get_indirect_rw_data]input: data_id = %d\n",param_1);
  }
  if (param_1 < 6) {
    iVar2 = tmOnuRegRead(6,&local_14,param_1,&spaRegTable);
    if (iVar2 == 0) {
      *param_2 = local_14;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][spa_get_indirect_rw_data]output: rw_data = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][spa_get_indirect_rw_data]reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][spa_get_indirect_rw_data]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

