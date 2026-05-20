// module: tm.ko
// function: tm_acl_find_filter @ 0x6ae00
// size: 444 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 tm_acl_find_filter(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (param_1 == 0) {
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: flow_config=NULL\n","zte_sw_api.c",param_3,g_tm_debug_level,param_4)
      ;
      return 0xffffffff;
    }
  }
  else {
    if (param_2 != (undefined4 *)0x0) {
      if (g_AclFilter_Head != (undefined4 *)0x0) {
        puVar3 = (undefined4 *)0x0;
        puVar2 = g_AclFilter_Head;
        do {
          while ((puVar2[2] == *(int *)(param_1 + 4) &&
                 (iVar1 = tm_acl_check_matchfiled(puVar2 + 3,param_1 + 8), iVar1 == 1))) {
            if (1 < g_tm_debug_level) {
              printk("[%s] find all-field-match filter rule-index=%d\n","zte_sw_api.c",*puVar2,
                     g_tm_debug_level,param_4);
            }
            if (param_2[1] == 0) {
              __memzero(param_2,0x10);
              param_2[3] = 0;
              param_2[2] = 0;
              puVar3 = param_2;
            }
            else {
              iVar1 = kmem_cache_alloc(_DAT_000df0e4,0x20);
              puVar3[3] = iVar1;
              if (iVar1 == 0) {
                if (g_tm_debug_level != 0) {
                  printk("[%s] FAIL! p_acl_match_filter->next malloc fail!\n","zte_sw_api.c");
                  return 0xfffffff4;
                }
                return 0xfffffff4;
              }
              __memzero(iVar1,0x10);
              *(undefined4 **)(puVar3[3] + 8) = puVar3;
              *(undefined4 *)(puVar3[3] + 0xc) = 0;
              puVar3 = (undefined4 *)puVar3[3];
            }
            puVar3[1] = puVar2;
            *puVar3 = 1;
            puVar2 = (undefined4 *)puVar2[0x12e];
            if (puVar2 == (undefined4 *)0x0) {
              return 0;
            }
          }
          puVar2 = (undefined4 *)puVar2[0x12e];
        } while (puVar2 != (undefined4 *)0x0);
      }
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: match_filter=NULL\n","zte_sw_api.c",param_3,g_tm_debug_level,param_4
            );
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

