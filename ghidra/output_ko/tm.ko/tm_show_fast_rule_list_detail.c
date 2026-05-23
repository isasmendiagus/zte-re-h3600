// module: tm.ko
// function: tm_show_fast_rule_list_detail @ 0x6bce4
// size: 68 bytes
//

void tm_show_fast_rule_list_detail(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 0;
  piVar3 = (int *)((int)&g_fast_entry_v6 + 4);
  do {
    piVar3 = piVar3 + 1;
    for (iVar1 = *piVar3; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x48)) {
      tm_show_acl_rule_entry(iVar1 + 0x30,iVar2);
      iVar2 = iVar2 + 1;
    }
  } while (piVar3 != (int *)(g_FastList + 0x7fc));
  return;
}

