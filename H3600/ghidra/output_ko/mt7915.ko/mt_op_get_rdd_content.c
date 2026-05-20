// module: mt7915.ko
// function: mt_op_get_rdd_content @ 0x258a3c
// size: 468 bytes
//

undefined4 mt_op_get_rdd_content(int param_1,undefined4 *param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  uint extraout_r1;
  int extraout_r1_00;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  
  if (param_1 == 0) {
    printk("%s: log_cb == NULL\n","mt_op_get_rdd_content");
    return 0x503;
  }
  iVar4 = *(int *)(param_1 + 0x14);
  if (iVar4 == 0) {
    printk("%s: log_cb->entry == NULL\n","mt_op_get_rdd_content");
    return 0x503;
  }
  uVar6 = *(uint *)(param_1 + 0xc);
  if (uVar6 == 0) {
    printk("%s: RDD buffer size is empty\n","mt_op_get_rdd_content");
    return 0x503;
  }
  if (*(char *)(param_1 + 5) == '\x01') {
    uVar1 = *(uint *)(param_1 + 8);
    _LANCHOR0 = 0;
  }
  else {
    uVar1 = *(uint *)(param_1 + 8);
    if (uVar1 < _LANCHOR0) {
      uVar1 = (uVar6 + uVar1) - _LANCHOR0;
      goto LAB_00258a9c;
    }
  }
  uVar1 = uVar1 - _LANCHOR0;
LAB_00258a9c:
  uVar3 = _LANCHOR0;
  if (uVar1 < 0x51) {
    iVar2 = _LANCHOR0 + uVar1;
  }
  else {
    iVar2 = _LANCHOR0 + 0x50;
  }
  __aeabi_uidivmod(iVar2,uVar6);
  while( true ) {
    __aeabi_uidivmod(uVar3,uVar6);
    iVar4 = iVar4 + extraout_r1_00 * 0x1c;
    if (*(char *)(iVar4 + 4) != '\0') {
      puVar5 = param_2;
      iVar2 = iVar4;
      if (*(char *)(iVar4 + 0x10) == '\0') {
        puVar5 = param_2 + 2;
        *param_2 = *(undefined4 *)(iVar4 + 8);
        param_2[1] = *(undefined4 *)(iVar4 + 0xc);
        *param_3 = *param_3 + 2;
        iVar2 = *(int *)(param_1 + 0x14) + extraout_r1_00 * 0x1c;
      }
      *(undefined1 *)(iVar2 + 4) = 0;
      param_2 = puVar5 + 2;
      *puVar5 = *(undefined4 *)(iVar4 + 0x11);
      puVar5[1] = *(undefined4 *)(iVar4 + 0x15);
      *param_3 = *param_3 + 2;
      uVar6 = *(uint *)(param_1 + 0xc);
    }
    uVar3 = extraout_r1_00 + 1;
    if (uVar6 <= uVar3) {
      uVar3 = 0;
    }
    if (extraout_r1 == uVar3) break;
    iVar4 = *(int *)(param_1 + 0x14);
  }
  _LANCHOR0 = extraout_r1;
  if (*(uint *)(param_1 + 8) == extraout_r1) {
    _LANCHOR0 = 0;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  _raw_spin_lock_bh(param_1);
  *(undefined1 *)(param_1 + 6) = 0;
  _raw_spin_unlock_bh(param_1);
  *(undefined1 *)(param_1 + 5) = 0;
  return 0;
}

