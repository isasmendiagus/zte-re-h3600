// module: tm.ko
// function: tm_pm_g988_rule_set @ 0x55160
// size: 220 bytes
//

undefined4 tm_pm_g988_rule_set(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c;
  uint local_18;
  undefined1 auStack_14 [4];
  int local_10;
  int local_c;
  
  __memzero(&local_24,0x1c);
  tm_pm_port_get(param_1[3],auStack_14);
  local_18 = param_1[2];
  local_10 = param_1[4];
  local_c = param_1[5];
  if (param_1[3] == 5) {
    local_1c = local_18 != 1;
  }
  else if (local_18 < 2) {
    local_1c = (undefined1)local_18;
  }
  local_20 = *param_1;
  if (local_c == 0xffff) {
    if (local_10 == 0xffff) {
      local_24 = 0;
    }
    else {
      local_24 = 2;
    }
  }
  else if (local_10 == 0xffff) {
    local_24 = 1;
  }
  else {
    local_24 = 3;
  }
  iVar1 = pm_set_g988_cfg(&local_24);
  uVar2 = 0;
  if (iVar1 != 0) {
    if (g_tm_debug_level < 7) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][tm_pm_g988_rule_set]failed!\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

