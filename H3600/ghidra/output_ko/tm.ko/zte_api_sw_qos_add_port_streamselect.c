// module: tm.ko
// function: zte_api_sw_qos_add_port_streamselect @ 0x6b408
// size: 1376 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 zte_api_sw_qos_add_port_streamselect(byte *param_1,undefined4 *param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  undefined1 auStack_26c [20];
  undefined1 auStack_258 [100];
  undefined4 local_1f4 [20];
  undefined4 local_1a4;
  undefined1 auStack_190 [2];
  undefined2 local_18e;
  byte local_18c;
  char local_18b;
  undefined1 auStack_d4 [4];
  byte local_d0;
  char local_cf;
  
  __memzero(auStack_190,0xbc);
  __memzero(auStack_258,100);
  __memzero(auStack_26c,0x14);
  __memzero(auStack_d4,0xbc);
  __memzero(local_1f4,100);
  if (1 < g_tm_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %x\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n"
           ,"zte_sw_api.c","FlowConfig.ruleType",*param_1,"FlowConfig.rulePri",param_1[1],
           "FlowConfig.index",*(undefined2 *)(param_1 + 2),"FlowConfig.direction",
           *(undefined4 *)(param_1 + 4),"FlowConfig.match.entrynum",param_1[8],
           "FlowConfig.fwd.fwdmode",*(undefined4 *)(param_1 + 0x24c),"FlowConfig.fwd.desportmsk",
           *(undefined4 *)(param_1 + 0x250),"FlowConfig.fwd.gemport",
           *(undefined2 *)(param_1 + 0x254),"FlowConfig.fwd.desq",param_1[0x256],
           "FlowConfig.fwd.reserved",param_1[599],"FlowConfig.action.actionnum",param_1[600]);
  }
  iVar3 = tm_cla_get_parse_info(param_1,auStack_190);
  if (iVar3 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[%s] tm_cla_get_parse_info FAIL!\n","zte_sw_api.c");
    }
    return 0xffffffff;
  }
  iVar3 = tm_cla_get_oper_info(param_1,auStack_258,auStack_190);
  if (iVar3 != 0) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[%s] tm_cla_get_oper_info FAIL!\n","zte_sw_api.c");
    return 0xffffffff;
  }
  piVar4 = (int *)kmem_cache_alloc(_DAT_000df0e4,0x20);
  if (piVar4 == (int *)0x0) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[%s] p_aclMatchFilterHead malloc fail!\n","zte_sw_api.c");
    return 0xffffffff;
  }
  __memzero(piVar4,0x10);
  *piVar4 = 0;
  piVar4[1] = 0;
  piVar4[2] = 0;
  piVar4[3] = 0;
  _raw_spin_lock_bh(&acl_api_lock);
  tm_acl_find_filter(param_1,piVar4);
  if ((*param_1 - 3 < 2) && (tm_stream_l3_mtu_get(&local_18e), 1 < g_tm_debug_level)) {
    printk("[%s] new rule MTU=%d\n","zte_sw_api.c",local_18e);
  }
  iVar3 = tm_add_acl_flow_rule(auStack_190,auStack_258,auStack_26c);
  if (iVar3 != 0) {
LAB_0006b708:
    tm_acl_free_match_filter(piVar4);
    _raw_spin_unlock_bh(&acl_api_lock);
    return 0xffffffff;
  }
  iVar3 = tm_acl_add_rule_node(param_1,param_2,auStack_190,auStack_26c);
  uVar2 = g_tm_debug_level;
  if (iVar3 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[%s] tm_acl_add_rule_node FAIL!\n","zte_sw_api.c");
    }
    goto LAB_0006b708;
  }
  piVar5 = piVar4;
  if ((local_18b != '\0') && (local_18c < 0x20)) {
    g_BuctetAvail[local_18c] = 1;
    if (uVar2 < 2) goto LAB_0006b598;
    printk("[%s] output: ratelimit bktid=%d is occupied\n","zte_sw_api.c");
  }
  if (1 < g_tm_debug_level) {
    printk("[%s] output: rule_index=%d, avail_rule_num=%d\n","zte_sw_api.c",*param_2,param_2[1]);
  }
LAB_0006b598:
  do {
    if ((*piVar5 == 1) && ((undefined4 *)piVar5[1] != (undefined4 *)0x0)) {
      if (1 < g_tm_debug_level) {
        printk("[%s] find all-field-match filter rule-index=%d\n","zte_sw_api.c",
               *(undefined4 *)piVar5[1]);
      }
      __memzero(auStack_d4,0xbc);
      __memzero(local_1f4,100);
      iVar3 = piVar5[1];
      if (0x10 < *(byte *)(iVar3 + 0x25c)) {
        if (g_tm_debug_level != 0) {
          printk("[%s] get match rule oper info FAIL!\n","zte_sw_api.c");
        }
        goto LAB_0006b708;
      }
      if (1 < g_tm_debug_level) {
        printk("[%s] match rule operMsk=0x%x vlanOper=%d\n","zte_sw_api.c",local_1f4[0],local_1a4);
        iVar3 = piVar5[1];
      }
      iVar3 = tm_del_acl_flow_rule(iVar3 + 0x4a0,*(undefined4 *)(iVar3 + 8));
      if (iVar3 != 0) {
        if (g_tm_debug_level != 0) {
          printk("[%s] tm_del_acl_flow_rule FAIL!\n","zte_sw_api.c");
        }
        goto LAB_0006b708;
      }
      if (1 < g_tm_debug_level) {
        printk("[%s] tm_del_acl_flow_rule SUCCESS!\n","zte_sw_api.c");
      }
      iVar3 = tm_acl_delete_rule_node(piVar5);
      uVar2 = g_tm_debug_level;
      if (iVar3 != 0) {
        if (g_tm_debug_level != 0) {
          printk("[%s] tm_acl_delete_rule_node FAIL!\n","zte_sw_api.c");
        }
        goto LAB_0006b708;
      }
      if ((local_cf != '\0') && (local_d0 < 0x20)) {
        g_BuctetAvail[local_d0] = 0;
        if (uVar2 < 2) goto LAB_0006b58c;
        printk("[%s] release ratelimit bktid=%d\n","zte_sw_api.c");
      }
      if (1 < g_tm_debug_level) {
        printk("[%s] tm_acl_delete_rule_node SUCCESS: g_AclRule_num=%d\n","zte_sw_api.c",
               g_AclRule_Num);
      }
    }
LAB_0006b58c:
    piVar1 = piVar5 + 3;
    piVar5 = (int *)*piVar1;
    if ((int *)*piVar1 == (int *)0x0) {
      tm_acl_free_match_filter(piVar4);
      _raw_spin_unlock_bh(&acl_api_lock);
      return 0;
    }
  } while( true );
}

