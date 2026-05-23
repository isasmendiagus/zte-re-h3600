// module: tm.ko
// function: zte_api_get_zte_statistics @ 0x6510c
// size: 64 bytes
//

undefined4 zte_api_get_zte_statistics(void)

{
  int iVar1;
  
  iVar1 = tm_pm_zte_statistics_get();
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][zte_api_get_zte_statistics]failed!\n");
  return 0xffffffff;
}

