// module: tm.ko
// function: spa_get_indirect_rw_status @ 0x37d9c
// size: 152 bytes
//

undefined4 spa_get_indirect_rw_status(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(5,local_14,0,&spaRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][spa_get_indirect_rw_status]output: access_done = %d\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][spa_get_indirect_rw_status]reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

