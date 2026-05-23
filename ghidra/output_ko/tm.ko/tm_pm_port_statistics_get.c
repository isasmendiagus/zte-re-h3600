// module: tm.ko
// function: tm_pm_port_statistics_get @ 0x550cc
// size: 148 bytes
//

void tm_pm_port_statistics_get(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_54 [2];
  undefined1 auStack_4c [4];
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  
  __memzero(&local_48,0x30);
  __memzero(local_54,0xc);
  tm_pm_port_get(param_1[2],auStack_4c);
  local_54[0] = *param_1;
  iVar1 = pm_get_port_statistics_cfg(local_54,&local_48);
  if (iVar1 != 0) {
    tm_pm_port_statistics_get_part_46();
    return;
  }
  *param_2 = local_48;
  param_2[1] = uStack_44;
  param_2[2] = local_40;
  param_2[4] = local_38;
  param_2[5] = uStack_34;
  param_2[6] = local_30;
  param_2[8] = local_28;
  param_2[9] = uStack_24;
  param_2[10] = local_20;
  return;
}

