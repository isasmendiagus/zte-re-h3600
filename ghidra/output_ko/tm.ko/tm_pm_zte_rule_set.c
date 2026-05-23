// module: tm.ko
// function: tm_pm_zte_rule_set @ 0x553c8
// size: 148 bytes
//

undefined4 tm_pm_zte_rule_set(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined1 auStack_10 [4];
  int local_c;
  
  __memzero(&local_1c,0x14);
  tm_pm_port_get(param_1[3],auStack_10);
  local_c = param_1[2];
  local_18 = *param_1;
  local_14 = param_1[1];
  local_1c = (uint)(local_c == 0xffff);
  iVar1 = pm_set_zte_cfg(&local_1c);
  uVar2 = 0;
  if (iVar1 != 0) {
    if (g_tm_debug_level < 7) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][tm_pm_zte_rule_set]failed!\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

