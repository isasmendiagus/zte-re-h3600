// module: tm.ko
// function: cla_set_outspace_cfg @ 0x112e0
// size: 192 bytes
//

undefined4 cla_set_outspace_cfg(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_outspace_cfg]input: outer_hash_num = %d,outer_space_sel=%d\n",param_1,
           param_2);
  }
  bVar3 = 2 < param_1;
  bVar2 = param_1 == 3;
  if (3 < param_1) {
    bVar3 = 3 < param_2;
    bVar2 = param_2 == 4;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_set_outspace_cfg]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0xd,param_2 & 3 | (param_1 & 3) << 2,0,&claRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_set_outspace_cfg]reg write failed\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

