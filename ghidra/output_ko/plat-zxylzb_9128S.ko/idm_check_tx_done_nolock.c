// module: plat-zxylzb_9128S.ko
// function: idm_check_tx_done_nolock @ 0x156dc
// size: 268 bytes
//

int idm_check_tx_done_nolock(void)

{
  ushort uVar1;
  uint uVar2;
  undefined4 in_r3;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar3 = *(uint *)(npp_base + 0x8044) & 0xffff;
  if (uVar3 != 0) {
    uVar2 = 0;
    if (0xff < uVar3) {
      uVar3 = 0x100;
    }
    do {
      uVar4 = uVar2;
      uVar2 = idm_tx_done + 1;
      iVar5 = *(int *)(skb_tq + idm_tx_done * 4);
      if (0x3ff < uVar2) {
        uVar2 = 0;
      }
      *(undefined4 *)(skb_tq + idm_tx_done * 4) = 0;
      idm_tx_done = uVar2;
      if (iVar5 == 0) {
        idm_txtq_err = idm_txtq_err + 1;
      }
      else {
        uVar1 = *(ushort *)(iVar5 + 0xbc);
        if ((uVar1 & 0x20) == 0) {
          if ((uVar1 & 0x40) == 0) {
            __dev_kfree_skb_any(iVar5,1);
          }
          else {
            _idm_skb_stack_push(iVar5,2,uVar2,uVar1,in_r3);
          }
        }
        else {
          _idm_skb_stack_push(iVar5,1,uVar2,uVar1,in_r3);
        }
      }
      uVar2 = uVar4 + 1;
    } while (uVar2 != uVar3);
    iVar5 = uVar4 + 1;
    *(int *)(npp_base + 0x8040) = iVar5;
    idm_tx_done_total = iVar5 + idm_tx_done_total;
    idm_skb_tx = idm_skb_tx - iVar5;
    return 0x100 - iVar5;
  }
  return 0x100;
}

