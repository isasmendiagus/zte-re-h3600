// module: tm.ko
// function: zte_api_sw_qos_del_port_streamselect @ 0x6b96c
// size: 884 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 zte_api_sw_qos_del_port_streamselect(undefined1 *param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined1 auStack_260 [100];
  undefined4 local_1fc [20];
  undefined4 local_1ac;
  undefined1 auStack_198 [188];
  undefined1 auStack_dc [4];
  byte local_d8;
  char local_d7;
  
  __memzero(auStack_198,0xbc);
  __memzero(auStack_260,100);
  if (1 < g_tm_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n","zte_sw_api.c",
           "FlowConfig.ruleType",*param_1,"FlowConfig.rulePri",param_1[1],"FlowConfig.index",
           *(undefined2 *)(param_1 + 2),"FlowConfig.direction",*(undefined4 *)(param_1 + 4),
           "FlowConfig.match.entrynum",param_1[8]);
  }
  iVar2 = tm_cla_get_parse_info(param_1,auStack_198);
  if (iVar2 == 0) {
    piVar3 = (int *)kmem_cache_alloc(_DAT_000df0e4,0x20);
    if (piVar3 == (int *)0x0) {
      if (g_tm_debug_level == 0) {
        uVar5 = 0xfffffff4;
      }
      else {
        printk("[%s] FAIL! p_aclMatchFilterHead malloc fail!\n","zte_sw_api.c");
        uVar5 = 0xfffffff4;
      }
    }
    else {
      __memzero(piVar3,0x10);
      *piVar3 = 0;
      piVar3[1] = 0;
      piVar3[2] = 0;
      piVar3[3] = 0;
      _raw_spin_lock_bh(&acl_api_lock);
      tm_acl_find_filter(param_1,piVar3);
      piVar4 = piVar3;
      while ((*piVar4 != 1 || ((undefined4 *)piVar4[1] == (undefined4 *)0x0))) {
LAB_0006ba2c:
        piVar4 = (int *)piVar4[3];
        if (piVar4 == (int *)0x0) {
          tm_acl_free_match_filter(piVar3);
          _raw_spin_unlock_bh(&acl_api_lock);
          return 0;
        }
      }
      if (1 < g_tm_debug_level) {
        printk("[%s] find all-field-match filter rule-index=%d\n","zte_sw_api.c",
               *(undefined4 *)piVar4[1]);
      }
      __memzero(auStack_dc,0xbc);
      __memzero(local_1fc,100);
      iVar2 = piVar4[1];
      if (*(byte *)(iVar2 + 0x25c) < 0x11) {
        if (1 < g_tm_debug_level) {
          printk("[%s] match rule operMsk=0x%x vlanOper=%d\n","zte_sw_api.c",local_1fc[0],local_1ac)
          ;
          iVar2 = piVar4[1];
        }
        iVar2 = tm_del_acl_flow_rule(iVar2 + 0x4a0,*(undefined4 *)(iVar2 + 8));
        if (iVar2 == 0) {
          if (1 < g_tm_debug_level) {
            printk("[%s] tm_del_acl_flow_rule SUCCESS!\n","zte_sw_api.c");
          }
          iVar2 = tm_acl_delete_rule_node(piVar4);
          uVar1 = g_tm_debug_level;
          if (iVar2 == 0) {
            if ((local_d7 != '\0') && (local_d8 < 0x20)) {
              g_BuctetAvail[local_d8] = 0;
              if (uVar1 < 2) goto LAB_0006ba2c;
              printk("[%s] output: release ratelimit bktid=%d\n","zte_sw_api.c");
            }
            if (1 < g_tm_debug_level) {
              printk("[%s] SUCCESS: g_AclRule_num=%d\n","zte_sw_api.c",g_AclRule_Num);
            }
            goto LAB_0006ba2c;
          }
          if (g_tm_debug_level != 0) {
            printk("[%s] sw_acl_delete_rule_node FAIL!\n","zte_sw_api.c");
          }
        }
        else if (g_tm_debug_level != 0) {
          printk("[%s] tm_del_acl_flow_rule FAIL!\n","zte_sw_api.c");
        }
      }
      else if (g_tm_debug_level != 0) {
        printk("[%s] get match rule oper info FAIL!\n","zte_sw_api.c");
      }
      uVar5 = 0xffffffff;
      tm_acl_free_match_filter(piVar3);
      _raw_spin_unlock_bh(&acl_api_lock);
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar5 = 0xffffffff;
  }
  else {
    printk("[%s] tm_cla_get_parse_info FAIL!\n","zte_sw_api.c");
    uVar5 = 0xffffffff;
  }
  return uVar5;
}

