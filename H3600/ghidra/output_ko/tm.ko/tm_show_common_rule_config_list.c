// module: tm.ko
// function: tm_show_common_rule_config_list @ 0x679e8
// size: 48 bytes
//

void tm_show_common_rule_config_list(void)

{
  int iVar1;
  
  iVar1 = g_AclFilter_Head;
  if (g_AclFilter_Head == 0) {
    return;
  }
  do {
    tm_print_common_rule_config(iVar1);
    iVar1 = *(int *)(iVar1 + 0x4b8);
  } while (iVar1 != 0);
  return;
}

