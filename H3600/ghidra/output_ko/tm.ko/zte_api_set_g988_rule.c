// module: tm.ko
// function: zte_api_set_g988_rule @ 0x64dd0
// size: 308 bytes
//

undefined4 zte_api_set_g988_rule(int *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  
  iVar1 = tm_pm_g988_rule_set();
  if (iVar1 != 0) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][zte_api_set_g988_rule]failed!\n");
    return 0xffffffff;
  }
  puVar2 = port_g988stat_last;
  iVar1 = 0;
  do {
    if (*param_1 == 0) {
      if ((((param_1[3] == *(int *)(puVar2 + 4)) && (param_1[5] == *(int *)(puVar2 + 8))) &&
          (param_1[4] == *(int *)(puVar2 + 0xc))) && (param_1[2] == *(int *)(puVar2 + 0x10))) {
        iVar1 = iVar1 * 0x80;
        *(undefined4 *)(port_g988stat_last + iVar1) = 2;
        *(undefined4 *)(port_g988stat_last + iVar1 + 8) = 0xfff;
        *(undefined4 *)(port_g988stat_last + iVar1 + 0x10) = 2;
        *(undefined4 *)(port_g988stat_last + iVar1 + 4) = 8;
        *(undefined4 *)(port_g988stat_last + iVar1 + 0xc) = 8;
        return 0;
      }
    }
    else if ((*param_1 == 1) && (*(int *)(puVar2 + 0x10) == 2)) {
      iVar1 = iVar1 * 0x80;
      *(undefined4 *)(port_g988stat_last + iVar1) = 1;
      *(int *)(port_g988stat_last + iVar1 + 4) = param_1[3];
      *(int *)(port_g988stat_last + iVar1 + 8) = param_1[5];
      *(int *)(port_g988stat_last + iVar1 + 0xc) = param_1[4];
      *(int *)(port_g988stat_last + iVar1 + 0x10) = param_1[2];
      return 0;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0x80;
    if (iVar1 == 0x40) {
      return 0;
    }
  } while( true );
}

