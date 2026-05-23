// module: mt7915.ko
// function: pci_rx_data_done_func @ 0x1cc170
// size: 460 bytes
//

void pci_rx_data_done_func(int param_1)

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
  iVar8 = *(int *)(param_1 + 0x70);
  uVar5 = *(uint *)(param_1 + 0x6c);
  iVar6 = param_1 + 0xc0;
  if (*(char *)(iVar1 + 0x2f5ec) != '\0') {
    ba_timeout_flush();
    uVar2 = _raw_spin_lock_irqsave(iVar6);
    if (((uVar5 & *(uint *)(param_1 + 0xc)) == 0) && ((uVar5 & *(uint *)(param_1 + 8)) == 0))
    goto LAB_001cc2b8;
    _raw_spin_unlock_irqrestore(iVar6,uVar2);
  }
  if ((*(uint *)(iVar1 + 0xa39f84) & 0x100) != 0) {
    uVar2 = _raw_spin_lock_irqsave(iVar6);
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~uVar5;
    _raw_spin_unlock_irqrestore(iVar6,uVar2);
    return;
  }
  uVar2 = _raw_spin_lock_irqsave(iVar6);
  uVar9 = *(uint *)(param_1 + 0xc);
  *(uint *)(param_1 + 0xc) = uVar9 & ~uVar5;
  _raw_spin_unlock_irqrestore(iVar6,uVar2);
  if (iVar8 != 0) {
    pbVar7 = (byte *)(param_1 + 0x73);
    iVar12 = 0;
    do {
      while( true ) {
        pbVar7 = pbVar7 + 1;
        iVar11 = *(int *)(param_1 + 0x14) + (uint)*pbVar7 * 0xa0;
        if ((((uVar9 & *(uint *)(iVar11 + 100)) == 0) &&
            (iVar3 = _test_and_clear_bit(iVar12,&DAT_005f48f8), iVar3 == 0)) ||
           (iVar11 = (**(code **)(iVar10 + 0x1c))(iVar1,*(undefined1 *)(iVar11 + 0x1c)), iVar11 == 0
           )) break;
        iVar11 = iVar12 + 1;
        _set_bit(iVar12,&DAT_005f48f8);
        iVar12 = iVar11;
        if (iVar11 == iVar8) goto LAB_001cc270;
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 != iVar8);
  }
LAB_001cc270:
  uVar2 = _raw_spin_lock_irqsave(iVar6);
  if (((uVar5 & *(uint *)(param_1 + 0xc)) == 0) && (DAT_005f48f8 == 0)) {
    mt_int_enable(iVar1,param_1,uVar5);
  }
  else {
    (**(code **)(iVar4 + 4))(param_1 + 0xe0);
  }
LAB_001cc2b8:
  _raw_spin_unlock_irqrestore(iVar6,uVar2);
  return;
}

