// module: mt7915.ko
// function: tx_flow_check_state @ 0xce4dc
// size: 204 bytes
//

undefined4 tx_flow_check_state(int param_1,uint param_2,int param_3)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = hif_get_tx_res_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_3 == iVar2) {
    if (param_3 != 0) {
      iVar2 = 0;
      do {
        _raw_spin_lock_bh(*(int *)(param_1 + 0x9daa8) + iVar2 * 4);
        pbVar1 = (byte *)(*(int *)(param_1 + 0x9daa4) + iVar2);
        iVar3 = *(int *)(param_1 + 0x9daa8) + iVar2 * 4;
        iVar2 = iVar2 + 1;
        if ((*pbVar1 & param_2) == param_2) goto LAB_000ce59c;
        _raw_spin_unlock_bh(iVar3);
      } while (iVar2 != (param_3 - 1U & 0xff) + 1);
    }
  }
  else {
    _raw_spin_lock_bh(*(int *)(param_1 + 0x9daa8) + param_3 * 4);
    iVar3 = *(int *)(param_1 + 0x9daa8) + param_3 * 4;
    if (param_2 == (*(byte *)(*(int *)(param_1 + 0x9daa4) + param_3) & param_2)) {
LAB_000ce59c:
      _raw_spin_unlock_bh(iVar3);
      return 1;
    }
    _raw_spin_unlock_bh(iVar3);
  }
  return 0;
}

