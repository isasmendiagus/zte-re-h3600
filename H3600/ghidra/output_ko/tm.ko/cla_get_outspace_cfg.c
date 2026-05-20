// module: tm.ko
// function: cla_get_outspace_cfg @ 0x113a0
// size: 164 bytes
//

undefined4 cla_get_outspace_cfg(uint *param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0xd,local_14,0,&claRegTable);
  *param_1 = (local_14[0] << 0x1c) >> 0x1e;
  *param_2 = local_14[0] & 3;
  if (iVar1 == 0) {
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][cla_get_outspace_cfg]output: outer_hash_num = %d, outer_space_sel = %d\n",
             *param_1);
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_outspace_cfg]reg write failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

