// module: tm.ko
// function: tm_add_acl_flow_rule @ 0x5f430
// size: 288 bytes
//

int tm_add_acl_flow_rule(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint local_14;
  
  local_14 = 0;
  if (param_1 == 0 || (param_3 == 0 || param_2 == 0)) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0x2409);
    printk("param is NULL\n");
    iVar1 = -0xc;
  }
  else {
    _raw_spin_lock_bh(&acl_api_busy_lock);
    g_qosEn = *(int *)(param_1 + 0xc) == 2;
    iVar1 = addFlowOperInfo(param_2,param_1,&local_14);
    if (iVar1 == 0) {
      if ((g_fast_opti == 0) || (5 < *(int *)(param_1 + 0xc) - 3U)) {
        iVar1 = addAclRule();
      }
      else {
        iVar1 = tm_acl_fast_add(param_1,local_14,param_3);
      }
      if ((iVar1 != 0) && ((local_14 & 0x7fffffff) != 0)) {
        operInfoDel(local_14,*(undefined4 *)(param_1 + 0x10));
      }
    }
    _raw_spin_unlock_bh(&acl_api_busy_lock);
  }
  return iVar1;
}

