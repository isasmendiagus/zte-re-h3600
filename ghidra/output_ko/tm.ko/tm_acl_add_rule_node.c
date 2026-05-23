// module: tm.ko
// function: tm_acl_add_rule_node @ 0x6b070
// size: 464 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 tm_acl_add_rule_node(void *param_1,int *param_2,int param_3,int *param_4)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  bool bVar9;
  
  if ((param_2 == (int *)0x0 || param_1 == (void *)0x0) || (param_4 == (int *)0x0 || param_3 == 0))
  {
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: point=NULL\n","zte_sw_api.c",param_3,g_tm_debug_level,param_4);
      return 0xffffffff;
    }
  }
  else {
    iVar5 = 0;
    pcVar7 = zte_onu_dipv6 + 0xf;
    do {
      pcVar7 = pcVar7 + 1;
      if (*pcVar7 == '\0') {
        piVar3 = (int *)kmem_cache_alloc(_DAT_000df0fc,0x20);
        if (piVar3 != (int *)0x0) {
          __memzero(piVar3,0x4bc);
          piVar3[0x12e] = 0;
          piVar3[0x12d] = 0;
          *piVar3 = iVar5;
          memcpy(piVar3 + 1,param_1,0x49c);
          iVar4 = *param_4;
          bVar9 = g_AclFilter_Head != (int *)0x0;
          iVar6 = param_4[1];
          iVar8 = param_4[2];
          piVar3[299] = param_4[3];
          piVar3[0x128] = iVar4;
          g_AclRule_Num = (int *)((int)g_AclRule_Num + 1);
          piVar3[0x129] = iVar6;
          piVar3[0x12a] = iVar8;
          piVar1 = g_AclFilter_Tail;
          if (!bVar9) {
            piVar1 = g_AclRule_Num;
            g_AclFilter_Tail = piVar3;
          }
          piVar3[300] = param_4[4];
          g_AclRuleIsUse_Flag[iVar5] = 1;
          piVar2 = piVar3;
          if (bVar9) {
            g_AclFilter_Tail = piVar3;
            piVar1[0x12e] = (int)piVar3;
            piVar3[0x12d] = (int)piVar1;
            piVar2 = g_AclFilter_Head;
          }
          g_AclFilter_Head = piVar2;
          *param_2 = *piVar3;
          param_2[1] = 0x2000 - (int)g_AclRule_Num;
          return 0;
        }
        if (g_tm_debug_level != 0) {
          printk("[%s] FAIL! p_newAclFilterNode malloc fail!\n","zte_sw_api.c");
          return 0xfffffff4;
        }
        return 0xfffffff4;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 != 0x2000);
    if (g_tm_debug_level != 0) {
      printk("[%s] FAIL! No Avail Acl Rule Node, g_AclRule_Num=%d\n","zte_sw_api.c",g_AclRule_Num,
             0xde3c0,param_4);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

