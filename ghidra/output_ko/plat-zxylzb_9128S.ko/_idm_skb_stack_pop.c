// module: plat-zxylzb_9128S.ko
// function: _idm_skb_stack_pop @ 0x14bb0
// size: 172 bytes
//

int _idm_skb_stack_pop(int param_1)

{
  int iVar1;
  ushort uVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar1 = param_1 * 4;
  puVar5 = &idm_lock_stack + param_1;
  _raw_spin_lock_bh(puVar5);
  if (*(int *)(idm_skb_stack_idx + iVar1) != 0) {
    iVar4 = *(int *)(idm_skb_stack_idx + iVar1) + -1;
    *(int *)(idm_skb_stack_idx + iVar1) = iVar4;
    iVar4 = *(int *)(idm_skb_stack + (iVar4 + param_1 * 0x400) * 4);
    _raw_spin_unlock_bh(puVar5);
    uVar2 = *(ushort *)(iVar4 + 0xbc);
    uVar3 = *(undefined2 *)(iVar4 + 0xbe);
    *(int *)(idm_pop_cnt + iVar1) = *(int *)(idm_pop_cnt + iVar1) + 1;
    skb_recycle(iVar4);
    if ((uVar2 & 1) != 0) {
      *(undefined2 *)(iVar4 + 0xbe) = uVar3;
      *(ushort *)(iVar4 + 0xbc) = *(ushort *)(iVar4 + 0xbc) | 1;
    }
    return iVar4;
  }
  _raw_spin_unlock_bh(puVar5);
  *(int *)(idm_skb_stack_empty + iVar1) = *(int *)(idm_skb_stack_empty + iVar1) + 1;
  return 0;
}

