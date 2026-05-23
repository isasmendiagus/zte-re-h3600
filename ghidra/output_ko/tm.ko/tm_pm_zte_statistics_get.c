// module: tm.ko
// function: tm_pm_zte_statistics_get @ 0x5545c
// size: 276 bytes
//

undefined4 tm_pm_zte_statistics_get(int param_1,undefined4 *param_2)

{
  int iVar1;
  uint local_64 [2];
  undefined4 local_5c;
  undefined1 auStack_58 [4];
  int local_54;
  undefined4 local_50 [2];
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  __memzero(local_50,0x38);
  __memzero(local_64,0x14);
  tm_pm_port_get(*(undefined4 *)(param_1 + 0xc),auStack_58);
  local_5c = *(undefined4 *)(param_1 + 4);
  local_54 = *(int *)(param_1 + 8);
  local_64[0] = (uint)(local_54 == 0xffff);
  iVar1 = pm_get_zte_statistics_cfg(local_64,local_50);
  if (iVar1 == 0) {
    *param_2 = local_50[0];
    param_2[2] = local_48;
    param_2[3] = uStack_44;
    param_2[4] = local_40;
    param_2[5] = uStack_3c;
    param_2[6] = uStack_38;
    if (local_64[0] == 1) {
      param_2[7] = 0;
      local_30 = 0;
    }
    else {
      param_2[7] = local_34;
    }
    param_2[8] = local_30;
    param_2[9] = local_2c;
    param_2[10] = local_28;
    param_2[0xb] = local_24;
    param_2[0xc] = local_20;
    return 0;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][tm_pm_zte_statistics_get]failed!\n");
  }
  return 0xffffffff;
}

