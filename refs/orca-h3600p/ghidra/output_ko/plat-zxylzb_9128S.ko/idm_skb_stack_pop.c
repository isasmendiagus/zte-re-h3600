// module: plat-zxylzb_9128S.ko
// function: idm_skb_stack_pop @ 0x14870
// size: 116 bytes
//

int idm_skb_stack_pop(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = param_1 + 1;
  if (((int)uVar3 < 3) && (iVar1 = _idm_skb_stack_pop(uVar3 & 0xff), iVar1 != 0)) {
    iVar2 = (*(int *)(iVar1 + 0xcc) - *(int *)(iVar1 + 0xd0)) + -0x20;
    if (param_2 <= iVar2) {
      return iVar1;
    }
    __dev_kfree_skb_any(iVar1,1,iVar2,iVar1,param_4);
    *(int *)(idm_pop_size_err + uVar3 * 4) = *(int *)(idm_pop_size_err + uVar3 * 4) + 1;
    return 0;
  }
  return 0;
}

