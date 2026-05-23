// module: mt7915.ko
// function: ba_reordering_resource_release @ 0xa551c
// size: 388 bytes
//

void ba_reordering_resource_release(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = param_1 + 0x1c0;
  iVar6 = param_1 + 0x1d0;
  iVar4 = iVar5;
  do {
    _raw_spin_lock_bh(iVar6);
    if (*(int *)(iVar6 + -8) != 0) {
      while( true ) {
        if (iVar6 == -0x1c) {
          printk(&_LC1,0x46);
          dump_stack();
        }
        puVar3 = *(undefined4 **)(iVar6 + 0x1c);
        if (puVar3 == (undefined4 *)0x0) break;
        *(int *)(iVar6 + 0x24) = *(int *)(iVar6 + 0x24) + -1;
        *(undefined4 *)(iVar6 + 0x1c) = *puVar3;
        puVar2 = (undefined4 *)puVar3[1];
        while (puVar2 != (undefined4 *)0x0) {
          puVar3[3] = puVar3[3] + -1;
          puVar3[1] = *puVar2;
          RTMPFreeNdisPacket(param_1,puVar2[4]);
          FUN_000a4510(iVar5,iVar4,puVar2);
          puVar2 = (undefined4 *)puVar3[1];
        }
        iVar1 = puVar3[4];
        if (iVar1 == 0) {
          printk(&_LC28,0x269);
          dump_stack();
          iVar1 = puVar3[4];
        }
        RTMPFreeNdisPacket(param_1,iVar1);
        FUN_000a4510(iVar5,iVar4,puVar3);
      }
    }
    iVar4 = iVar4 + 0x60;
    _raw_spin_unlock_bh(iVar6);
    iVar6 = iVar6 + 0x60;
  } while (iVar4 != param_1 + 0x1b1c0);
  if (*(int *)(param_1 + 0x1b194) != 0) {
    printk(&_LC2,0x271);
    dump_stack();
  }
  _raw_spin_lock_bh(param_1 + 0x2f5c8);
  os_free_mem(*(undefined4 *)(param_1 + 0x2f5c4));
  _raw_spin_unlock_bh(param_1 + 0x2f5c8);
  _raw_spin_lock_bh(param_1 + 0x2f5dc);
  os_free_mem(*(undefined4 *)(param_1 + 0x2f5d8));
  _raw_spin_unlock_bh(param_1 + 0x2f5dc);
  return;
}

