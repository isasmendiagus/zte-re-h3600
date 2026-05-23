// module: tm.ko
// function: tm_delete_fast_rule_node @ 0x637b8
// size: 132 bytes
//

void tm_delete_fast_rule_node(int param_1,int param_2)

{
  int iVar1;
  
  param_1 = param_1 * 4;
  if (*(int *)(g_FastList + param_1) == *(int *)(g_FastList_Tail + param_1)) {
    *(undefined4 *)(g_FastList + param_1) = 0;
    *(undefined4 *)(g_FastList_Tail + param_1) = 0;
  }
  else {
    iVar1 = *(int *)(param_2 + 0x44);
    if (iVar1 == 0) {
      *(undefined4 *)(*(int *)(param_2 + 0x48) + 0x44) = 0;
      *(undefined4 *)(g_FastList + param_1) = *(undefined4 *)(param_2 + 0x48);
    }
    else if (*(int *)(param_2 + 0x48) == 0) {
      *(undefined4 *)(iVar1 + 0x48) = 0;
      *(undefined4 *)(g_FastList_Tail + param_1) = *(undefined4 *)(param_2 + 0x44);
    }
    else {
      *(int *)(*(int *)(param_2 + 0x48) + 0x44) = iVar1;
      *(undefined4 *)(*(int *)(param_2 + 0x44) + 0x48) = *(undefined4 *)(param_2 + 0x48);
    }
  }
  kfree(param_2);
  return;
}

