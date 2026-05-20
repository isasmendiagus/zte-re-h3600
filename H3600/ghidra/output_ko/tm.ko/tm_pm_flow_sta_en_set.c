// module: tm.ko
// function: tm_pm_flow_sta_en_set @ 0x4d33c
// size: 64 bytes
//

undefined4 tm_pm_flow_sta_en_set(void)

{
  int iVar1;
  
  iVar1 = pm_set_flow_sta_en();
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level < 7) {
    return 0xffffffff;
  }
  printk("[TM][tm_pm_flow_sta_en_set]failed!\n");
  return 0xffffffff;
}

