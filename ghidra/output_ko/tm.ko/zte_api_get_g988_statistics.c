// module: tm.ko
// function: zte_api_get_g988_statistics @ 0x64f08
// size: 444 bytes
//

undefined4 zte_api_get_g988_statistics(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  iVar2 = tm_pm_g988_statistics_get();
  if (iVar2 == 0) {
    puVar4 = port_g988stat_last;
    puVar3 = port_g988stat_total;
    iVar2 = 0;
    do {
      iVar1 = iVar2 * 0x80;
      iVar2 = iVar2 + 1;
      if ((((*(int *)(port_g988stat_last + iVar1) == 1) &&
           (*(int *)(param_1 + 0xc) == *(int *)(puVar4 + 4))) &&
          (*(int *)(param_1 + 0x14) == *(int *)(puVar4 + 8))) &&
         ((*(int *)(param_1 + 0x10) == *(int *)(puVar4 + 0xc) &&
          (*(int *)(param_1 + 8) == *(int *)(puVar4 + 0x10))))) {
        sw_get_pm_overflow(param_2,puVar4 + 0x18,puVar3 + 0x18);
        sw_get_pm_overflow(param_2 + 8,puVar4 + 0x20,puVar3 + 0x20);
        sw_get_pm_overflow(param_2 + 0x10,puVar4 + 0x28,puVar3 + 0x28);
        sw_get_pm_overflow(param_2 + 0x18,puVar4 + 0x30,puVar3 + 0x30);
        sw_get_pm_overflow(param_2 + 0x20,puVar4 + 0x38,puVar3 + 0x38);
        sw_get_pm_overflow(param_2 + 0x28,puVar4 + 0x40,puVar3 + 0x40);
        sw_get_pm_overflow(param_2 + 0x30,puVar4 + 0x48,puVar3 + 0x48);
        sw_get_pm_overflow(param_2 + 0x38,puVar4 + 0x50,puVar3 + 0x50);
        sw_get_pm_overflow(param_2 + 0x40,puVar4 + 0x58,puVar3 + 0x58);
        sw_get_pm_overflow(param_2 + 0x48,puVar4 + 0x60,puVar3 + 0x60);
        sw_get_pm_overflow(param_2 + 0x50,puVar4 + 0x68,puVar3 + 0x68);
        sw_get_pm_overflow(param_2 + 0x58,puVar4 + 0x70,puVar3 + 0x70);
        sw_get_pm_overflow(param_2 + 0x60,puVar4 + 0x78,puVar3 + 0x78);
      }
      puVar4 = puVar4 + 0x80;
      puVar3 = puVar3 + 0x80;
    } while (iVar2 != 0x40);
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][zte_api_get_g988_statistics]failed!\n");
  }
  return 0xffffffff;
}

