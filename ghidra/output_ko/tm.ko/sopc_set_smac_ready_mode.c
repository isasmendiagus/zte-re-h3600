// module: tm.ko
// function: sopc_set_smac_ready_mode @ 0x37990
// size: 244 bytes
//

undefined4 sopc_set_smac_ready_mode(uint param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  uint local_1c [2];
  
  bVar5 = param_2 != 0;
  bVar4 = param_2 == 1;
  if (param_2 < 2) {
    bVar5 = 3 < param_1;
    bVar4 = param_1 == 4;
  }
  local_1c[0] = 0;
  if (!bVar5 || bVar4) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sopc_set_smac_ready_mode]input: port = %d, ready_mode = %d\n",param_1,param_2);
    }
    iVar2 = tmOnuRegRead(7,local_1c,0,&sopcRegTable);
    iVar3 = tmOnuRegWrite(7,local_1c[0] & ~(3 << (param_1 << 1 & 0xff)) |
                            param_2 << (param_1 << 1 & 0xff),0,&sopcRegTable);
    uVar1 = 0;
    if (iVar3 != 0 || iVar2 != 0) {
      if (g_tm_debug_level == 0) {
        uVar1 = 0xffffffff;
      }
      else {
        printk("[TM][sopc_set_smac_ready_mode]reg write failed\n");
        uVar1 = 0xffffffff;
      }
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sopc_set_smac_ready_mode]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

