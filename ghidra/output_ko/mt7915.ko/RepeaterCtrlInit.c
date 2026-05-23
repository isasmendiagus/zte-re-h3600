// module: mt7915.ko
// function: RepeaterCtrlInit @ 0x80ec0
// size: 520 bytes
//

void RepeaterCtrlInit(int param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  puVar3 = &DAT_00367914 + param_1;
  uVar4 = (uint)*(byte *)(iVar1 + 0x14a);
  _raw_spin_lock_bh(puVar3);
  if ((&DAT_0036790d)[param_1] == '\x01') {
    _raw_spin_unlock_bh(puVar3);
    if (1 < DebugLevel) {
      printk("%s, repeater feature already init. by one of bands repeater\n","RepeaterCtrlInit");
      return;
    }
    return;
  }
  iVar1 = os_alloc_mem(0,&DAT_003687a8 + param_1,uVar4 * 0x42f4);
  if (iVar1 != 0) {
    _raw_spin_unlock_bh(puVar3);
    if (-1 < DebugLevel) {
      printk(" Alloc memory for pRepeaterCliPool failed.\n");
      return;
    }
    return;
  }
  os_zero_mem(*(undefined4 *)(&DAT_003687a8 + param_1),uVar4 * 0x42f4);
  iVar1 = os_alloc_mem(0,&DAT_003687ac + param_1,uVar4 << 3);
  if (iVar1 == 0) {
    os_zero_mem(*(undefined4 *)(&DAT_003687ac + param_1),uVar4 << 3);
    if (uVar4 != 0) {
      iVar1 = 0;
      uVar5 = 0;
      do {
        iVar6 = *(int *)(&DAT_003687a8 + param_1);
        iVar2 = iVar6 + iVar1;
        *(undefined1 *)(iVar2 + 5) = 0;
        *(undefined1 *)(iVar2 + 6) = 0;
        *(undefined1 *)(iVar6 + iVar1) = 0;
        *(char *)(iVar2 + 4) = (char)uVar5;
        uVar5 = uVar5 + 1;
        *(undefined1 *)(iVar2 + 1) = 0;
        iVar1 = iVar1 + 0x42f4;
        *(int *)(iVar2 + 0x8c) = param_1;
        *(undefined1 *)(iVar2 + 2) = 0;
        *(undefined4 *)(iVar2 + 0x4144) = 0;
        *(undefined4 *)(iVar2 + 0x4148) = 0;
        *(undefined1 *)(iVar2 + 3) = 0;
        *(undefined4 *)(iVar2 + 0x9c) = 0;
        __init_waitqueue_head(iVar2 + 0xa0,"&x->wait",&g_u4TxBfOui);
      } while ((uVar5 & 0xff) < uVar4);
    }
    (&DAT_00367912)[param_1] = 0;
    (&DAT_00367913)[param_1] = 0;
    os_zero_mem(&DAT_00368120 + param_1,0x584);
    iVar1 = DebugLevel;
    (&DAT_0036790d)[param_1] = 1;
    if (0 < iVar1) {
      printk("%s() is done\n","RepeaterCtrlInit");
    }
  }
  else {
    if (*(int *)(&DAT_003687a8 + param_1) != 0) {
      os_free_mem();
    }
    if (-1 < DebugLevel) {
      printk(" Alloc memory for pRepeaterCliMapPool failed.\n");
    }
  }
  _raw_spin_unlock_bh(puVar3);
  return;
}

