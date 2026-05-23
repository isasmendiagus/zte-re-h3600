// module: tm.ko
// function: tm_pm_flow_statistics_get @ 0x4d37c
// size: 156 bytes
//

undefined4 tm_pm_flow_statistics_get(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_24;
  undefined4 local_20 [2];
  undefined4 local_18;
  undefined4 uStack_14;
  
  __memzero(local_20,0x10);
  pm_get_flow_sta_en(&local_24);
  if (local_24 == 0) {
    printk("flow_en is disabe!\n");
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = pm_get_flow_statistics_cfg(param_1,local_20);
    if (iVar1 == 0) {
      *param_2 = local_20[0];
      param_2[2] = local_18;
      param_2[3] = uStack_14;
      uVar2 = 0;
    }
    else if (g_tm_debug_level < 7) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][tm_pm_zte_statistics_get]failed!\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

