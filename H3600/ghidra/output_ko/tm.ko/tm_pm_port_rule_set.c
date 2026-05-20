// module: tm.ko
// function: tm_pm_port_rule_set @ 0x5505c
// size: 112 bytes
//

undefined4 tm_pm_port_rule_set(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined1 auStack_c [4];
  
  __memzero(&uStack_14,0xc);
  tm_pm_port_get(param_1[2],auStack_c);
  uStack_14 = *param_1;
  uStack_10 = param_1[1];
  iVar1 = pm_set_port_cfg(&uStack_14);
  uVar2 = 0;
  if (iVar1 != 0) {
    if (g_tm_debug_level < 7) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][tm_pm_port_rule_set]failed!\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

