// module: mt7915.ko
// function: pci_rx_event_done_func @ 0x1cbfe4
// size: 392 bytes
//

void pci_rx_event_done_func(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  
  iVar10 = *(int *)(param_1 + 0xd0);
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(iVar10 + 0xb0));
  iVar4 = *(int *)(param_1 + 0x6c0);
  iVar8 = *(int *)(param_1 + 0x98);
  uVar5 = *(uint *)(param_1 + 0x94);
  if ((*(uint *)(iVar1 + 0xa39f84) & 0x100) != 0) {
    uVar2 = _raw_spin_lock_irqsave(param_1 + 0xc0);
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~uVar5;
    _raw_spin_unlock_irqrestore(param_1 + 0xc0,uVar2);
    return;
  }
  iVar6 = param_1 + 0xc0;
  uVar2 = _raw_spin_lock_irqsave(iVar6);
  uVar9 = *(uint *)(param_1 + 0xc);
  *(uint *)(param_1 + 0xc) = uVar9 & ~uVar5;
  _raw_spin_unlock_irqrestore(iVar6,uVar2);
  if (iVar8 != 0) {
    pbVar7 = (byte *)(param_1 + 0x9b);
    iVar12 = 0;
    do {
      while( true ) {
        pbVar7 = pbVar7 + 1;
        iVar11 = *(int *)(param_1 + 0x14) + (uint)*pbVar7 * 0xa0;
        if ((((uVar9 & *(uint *)(iVar11 + 100)) == 0) &&
            (iVar3 = _test_and_clear_bit(iVar12,&DAT_005f48f4), iVar3 == 0)) ||
           (iVar11 = (**(code **)(iVar10 + 0x20))(iVar1,*(undefined1 *)(iVar11 + 0x1c)), iVar11 == 0
           )) break;
        iVar11 = iVar12 + 1;
        _set_bit(iVar12,&DAT_005f48f4);
        iVar12 = iVar11;
        if (iVar11 == iVar8) goto LAB_001cc0d4;
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 != iVar8);
  }
LAB_001cc0d4:
  uVar2 = _raw_spin_lock_irqsave(iVar6);
  if (((uVar5 & *(uint *)(param_1 + 0xc)) == 0) && (DAT_005f48f4 == 0)) {
    mt_int_enable(iVar1,param_1,uVar5);
  }
  else {
    (**(code **)(iVar4 + 8))(param_1 + 0xe0);
  }
  _raw_spin_unlock_irqrestore(iVar6,uVar2);
  return;
}

