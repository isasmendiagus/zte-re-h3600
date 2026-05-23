// module: tm.ko
// function: zte_api_fast_l3_session_del @ 0x66ca4
// size: 340 bytes
//

undefined4 zte_api_fast_l3_session_del(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  byte *local_14 [2];
  
  local_14[0] = (byte *)0x0;
  _raw_spin_lock_bh(&fast_api_busy_lock);
  uVar1 = cla_list_hash_addr_gen(param_1,0x28);
  iVar2 = tm_findFastIdxByTuple(uVar1 & 0x1ff,param_1,local_14);
  if (iVar2 == 0) {
    iVar2 = tm_del_acl_flow_rule(local_14[0] + 0x30,*local_14[0]);
    if (iVar2 == 0) {
      if ((*(uint *)(local_14[0] + 4) & 0xfffffffd) == 1) {
        iVar2 = *(int *)((int)&g_fast_entry_v6 + (uint)*local_14[0] * 4);
        if (iVar2 != 0) {
          *(int *)((int)&g_fast_entry_v6 + (uint)*local_14[0] * 4) = iVar2 + -1;
        }
      }
      else if ((&g_fast_entry_v4)[*local_14[0]] != 0) {
        (&g_fast_entry_v4)[*local_14[0]] = (&g_fast_entry_v4)[*local_14[0]] + -1;
      }
      tm_delete_fast_rule_node(uVar1 & 0x1ff);
      _raw_spin_unlock_bh(&fast_api_busy_lock);
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("[%s] tm_del_acl_flow_rule failed %d\n","zte_sw_api.c");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar3 = ___ratelimit(_rs_31604,"zte_api_fast_l3_session_del"), iVar3 != 0)) {
    printk("[%s] tm_findFastIdxByTuple failed %d\n","zte_sw_api.c",iVar2);
  }
  _raw_spin_unlock_bh(&fast_api_busy_lock);
  return 0xffffffff;
}

