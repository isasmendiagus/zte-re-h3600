// module: tm.ko
// function: tm_show_common_rule_list_detail @ 0x66e04
// size: 60 bytes
//

void tm_show_common_rule_list_detail(void)

{
  int iVar1;
  int iVar2;
  
  if (g_AclFilter_Head == 0) {
    return;
  }
  iVar2 = 0;
  iVar1 = g_AclFilter_Head;
  do {
    tm_show_acl_rule_entry(iVar1 + 0x4a0,iVar2);
    iVar1 = *(int *)(iVar1 + 0x4b8);
    iVar2 = iVar2 + 1;
  } while (iVar1 != 0);
  return;
}

