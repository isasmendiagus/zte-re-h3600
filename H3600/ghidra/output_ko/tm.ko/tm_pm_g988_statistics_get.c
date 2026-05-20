// module: tm.ko
// function: tm_pm_g988_statistics_get @ 0x5523c
// size: 396 bytes
//

undefined4 tm_pm_g988_statistics_get(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_84 [2];
  undefined1 local_7c;
  uint local_78;
  undefined1 auStack_74 [4];
  int local_70;
  int local_6c;
  undefined4 local_68 [2];
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  __memzero(local_68,0x40);
  __memzero(local_84,0x1c);
  tm_pm_port_get(*(undefined4 *)(param_1 + 0xc),auStack_74);
  local_78 = *(uint *)(param_1 + 8);
  local_70 = *(int *)(param_1 + 0x10);
  local_6c = *(int *)(param_1 + 0x14);
  if (*(int *)(param_1 + 0xc) == 5) {
    local_7c = local_78 != 1;
  }
  else if (local_78 < 2) {
    local_7c = (undefined1)local_78;
  }
  if (local_6c == 0xffff) {
    if (local_70 == 0xffff) {
      local_84[0] = 0;
    }
    else {
      local_84[0] = 2;
    }
  }
  else if (local_70 == 0xffff) {
    local_84[0] = 1;
  }
  else {
    local_84[0] = 3;
  }
  iVar1 = pm_get_g988_statistics_cfg(local_84,local_68);
  if (iVar1 != 0) {
    if (6 < g_tm_debug_level) {
      printk("[TM][tm_pm_g988_statistics_get]failed!\n");
    }
    return 0xffffffff;
  }
  *param_2 = local_68[0];
  param_2[0x12] = local_3c;
  param_2[1] = 0;
  param_2[5] = 0;
  param_2[0x14] = local_38;
  param_2[7] = 0;
  param_2[9] = 0;
  param_2[0xb] = 0;
  param_2[0xd] = 0;
  param_2[0xf] = 0;
  param_2[0x11] = 0;
  param_2[0x13] = 0;
  param_2[0x15] = 0;
  param_2[2] = local_60;
  param_2[3] = uStack_5c;
  param_2[4] = local_58;
  param_2[6] = local_54;
  param_2[8] = local_50;
  param_2[10] = local_4c;
  param_2[0xc] = local_48;
  param_2[0xe] = local_44;
  param_2[0x10] = local_40;
  param_2[0x16] = local_34;
  param_2[0x17] = 0;
  param_2[0x19] = 0;
  param_2[0x18] = local_30;
  return 0;
}

