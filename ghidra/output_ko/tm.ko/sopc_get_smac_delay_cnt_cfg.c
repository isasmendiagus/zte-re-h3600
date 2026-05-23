// module: tm.ko
// function: sopc_get_smac_delay_cnt_cfg @ 0x37714
// size: 152 bytes
//

undefined4 sopc_get_smac_delay_cnt_cfg(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(5,local_14,0,&sopcRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 0xffff;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sopc_get_smac_delay_cnt_cfg]output: delay_cnt = %d\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][sopc_get_smac_delay_cnt_cfg]reg write failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

