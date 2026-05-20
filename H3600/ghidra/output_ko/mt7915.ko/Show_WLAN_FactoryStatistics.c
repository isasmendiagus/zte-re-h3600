// module: mt7915.ko
// function: Show_WLAN_FactoryStatistics @ 0x15ef00
// size: 112 bytes
//

undefined4 Show_WLAN_FactoryStatistics(int *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*param_1 + 0x3c);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 3;
  }
  g_stWlanFactoryStatistics._4_4_ = param_1[(iVar1 >> 2) * 3 + 0xdb6ce];
  printk("\nInterrupt=%d\nBeacon=%d\nProbeRequest=%d\nProbeRespone=%d\n",
         g_stWlanFactoryStatistics._0_4_,g_stWlanFactoryStatistics._4_4_,
         g_stWlanFactoryStatistics._8_4_,g_stWlanFactoryStatistics._12_4_);
  return 1;
}

