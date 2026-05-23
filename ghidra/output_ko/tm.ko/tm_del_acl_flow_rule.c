// module: tm.ko
// function: tm_del_acl_flow_rule @ 0x5ed30
// size: 92 bytes
//

undefined4 tm_del_acl_flow_rule(undefined4 param_1,undefined4 param_2)

{
  uint local_14;
  
  local_14 = 0;
  _raw_spin_lock_bh(&acl_api_busy_lock);
  delAclRule(param_1,&local_14);
  if ((local_14 & 0x7fffffff) != 0) {
    operInfoDel(local_14,param_2);
  }
  _raw_spin_unlock_bh(&acl_api_busy_lock);
  return 0;
}

