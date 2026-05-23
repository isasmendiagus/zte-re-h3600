// module: plat-zxylzb_9128S.ko
// function: idm_skb_stack_push @ 0x156c0
// size: 28 bytes
//

void idm_skb_stack_push(int param_1)

{
  if ((*(ushort *)(param_1 + 0xbc) & 0x10) == 0) {
    __dev_kfree_skb_any(param_1,1);
    return;
  }
  _idm_skb_stack_push(param_1,0);
  return;
}

