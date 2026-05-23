// module: tm.ko
// function: tm_acl_free_match_filter @ 0x6b390
// size: 120 bytes
//

undefined4 tm_acl_free_match_filter(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar2 = *(int *)(param_1 + 0xc);
    while (iVar1 = iVar2, iVar1 != 0) {
      kfree(*(undefined4 *)(iVar1 + 8));
      param_1 = iVar1;
      iVar2 = *(int *)(iVar1 + 0xc);
    }
    kfree(param_1);
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[SW][tm_acl_free_match_filter] input ERROR: p_aclMatchFilter=NULL\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

