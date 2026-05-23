// module: plat-zxylzb_9128S.ko
// function: _idm_skb_stack_push @ 0x15154
// size: 384 bytes
//

undefined4 _idm_skb_stack_push(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  if ((*(int *)(param_1 + 0x68) == 0) && ((*(byte *)(param_1 + 0x72) & 0xc) == 0)) {
    if (*(int *)(param_1 + 0xcc) - *(int *)(param_1 + 0xd0) < 0x660) {
      idm_push_failed_res._12_4_ = idm_push_failed_res._12_4_ + 1;
    }
    else if (*(int *)(param_1 + 0xdc) == 1) {
      if (((*(byte *)(param_1 + 0x72) & 1) == 0) ||
         ((*(uint *)(*(int *)(param_1 + 0xcc) + 0x20) & 0xffff) == 1)) {
        iVar1 = param_2 * 4;
        puVar3 = &idm_lock_stack + param_2;
        _raw_spin_lock_bh(puVar3);
        uVar2 = *(uint *)(idm_skb_stack_idx + iVar1);
        if (0x3ff < uVar2) {
          _raw_spin_unlock_bh(puVar3);
          *(int *)(idm_skb_stack_full + iVar1) = *(int *)(idm_skb_stack_full + iVar1) + 1;
          __dev_kfree_skb_any(param_1);
          return 0xffffffff;
        }
        *(uint *)(idm_skb_stack_idx + iVar1) = uVar2 + 1;
        *(int *)(idm_skb_stack + (uVar2 + param_2 * 0x400) * 4) = param_1;
        _raw_spin_unlock_bh(puVar3);
        *(int *)(idm_push_cnt + iVar1) = *(int *)(idm_push_cnt + iVar1) + 1;
        return 0;
      }
      idm_push_failed_res._20_4_ = idm_push_failed_res._20_4_ + 1;
    }
    else {
      idm_push_failed_res._16_4_ = idm_push_failed_res._16_4_ + 1;
    }
  }
  else {
    idm_push_failed_res._8_4_ = idm_push_failed_res._8_4_ + 1;
  }
  *(int *)(idm_push_failed + param_2 * 4) = *(int *)(idm_push_failed + param_2 * 4) + 1;
  __dev_kfree_skb_any(param_1);
  return 0;
}

