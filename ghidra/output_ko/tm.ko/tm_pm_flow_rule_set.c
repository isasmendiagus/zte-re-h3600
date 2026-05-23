// module: tm.ko
// function: tm_pm_flow_rule_set @ 0x4d2c8
// size: 116 bytes
//

undefined4 tm_pm_flow_rule_set(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  __memzero(&local_18,0x10);
  local_18 = *param_1;
  uStack_14 = param_1[1];
  uStack_10 = param_1[2];
  uStack_c = param_1[3];
  iVar1 = pm_set_flow_cfg(&local_18);
  uVar2 = 0;
  if (iVar1 != 0) {
    if (g_tm_debug_level < 7) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][tm_pm_flow_rule_set]failed!\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

