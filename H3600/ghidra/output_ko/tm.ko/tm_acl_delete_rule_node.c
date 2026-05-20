// module: tm.ko
// function: tm_acl_delete_rule_node @ 0x6b244
// size: 332 bytes
//

undefined4
tm_acl_delete_rule_node(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint *puVar1;
  uint uVar2;
  
  if (param_1 == 0) {
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: p_aclMatchFilter=NULL\n","zte_sw_api.c",0,g_tm_debug_level,param_4);
      return 0xffffffff;
    }
  }
  else {
    puVar1 = *(uint **)(param_1 + 4);
    if (puVar1 != (uint *)0x0) {
      g_AclRule_Num = g_AclRule_Num + -1;
      if (*puVar1 < 0x2000) {
        g_AclRuleIsUse_Flag[*puVar1] = 0;
        puVar1 = *(uint **)(param_1 + 4);
      }
      if (g_AclFilter_Head == g_AclFilter_Tail) {
        g_AclFilter_Head = 0;
        g_AclFilter_Tail = 0;
      }
      else {
        uVar2 = puVar1[0x12d];
        if (uVar2 == 0) {
          if (puVar1[0x12e] != 0) {
            *(undefined4 *)(puVar1[0x12e] + 0x4b4) = 0;
            puVar1 = *(uint **)(param_1 + 4);
            g_AclFilter_Head = puVar1[0x12e];
          }
        }
        else if (puVar1[0x12e] == 0) {
          *(undefined4 *)(uVar2 + 0x4b8) = 0;
          puVar1 = *(uint **)(param_1 + 4);
          g_AclFilter_Tail = puVar1[0x12d];
        }
        else {
          *(uint *)(puVar1[0x12e] + 0x4b4) = uVar2;
          *(undefined4 *)(*(int *)(*(int *)(param_1 + 4) + 0x4b4) + 0x4b8) =
               *(undefined4 *)(*(int *)(param_1 + 4) + 0x4b8);
          puVar1 = *(uint **)(param_1 + 4);
        }
      }
      kfree(puVar1);
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("[%s] FAIL: p_global_acl_filter=NULL\n","zte_sw_api.c",param_1,g_tm_debug_level,param_4
            );
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

