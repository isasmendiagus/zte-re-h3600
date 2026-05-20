// module: tm.ko
// function: tm_cla_outspace_cfg_set @ 0x4c4c4
// size: 112 bytes
//

undefined4 tm_cla_outspace_cfg_set(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = 2 < param_1;
  bVar2 = param_1 == 3;
  if (3 < param_1) {
    bVar3 = 3 < param_2;
    bVar2 = param_2 == 4;
  }
  if (!bVar3 || bVar2) {
    iVar1 = cla_set_outspace_cfg();
    if (iVar1 == 0) {
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("[TM][tm_cla_outspace_cfg_set]failed\n");
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("[TM][tm_cla_outspace_cfg_set]input invalid parameter!\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

