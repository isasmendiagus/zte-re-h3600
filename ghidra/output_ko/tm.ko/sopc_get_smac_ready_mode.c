// module: tm.ko
// function: sopc_get_smac_ready_mode @ 0x37a84
// size: 248 bytes
//

undefined4 sopc_get_smac_ready_mode(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (param_1 < 5) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sopc_get_smac_ready_mode]input: port = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(7,local_1c,0,&sopcRegTable);
    if (iVar2 == 0) {
      *param_2 = local_1c[0] >> ((param_1 & 0x7f) << 1) & 3;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sopc_get_smac_ready_mode]output: ready_mode = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][sopc_get_smac_ready_mode]reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sopc_get_smac_ready_mode]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

