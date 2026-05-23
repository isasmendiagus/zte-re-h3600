// module: tm.ko
// function: cla_get_dn_unknown_da_action_cfg @ 0x11ecc
// size: 152 bytes
//

undefined4 cla_get_dn_unknown_da_action_cfg(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0x16,local_14,0,&claRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][cla_get_dn_unknown_da_action_cfg]output: act_val = %d\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_dn_unknown_da_action_cfg]reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

