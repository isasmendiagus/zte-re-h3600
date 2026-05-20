// module: mt7915.ko
// function: pci_rx_dly_done_func @ 0x1cb608
// size: 552 bytes
//

void pci_rx_dly_done_func(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  
  iVar8 = *(int *)(param_1 + 0xd0);
  iVar6 = param_1 + 0xc0;
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(iVar8 + 0xb0));
  iVar9 = *(int *)(param_1 + 0x6c0);
  uVar7 = *(uint *)(param_1 + 0x44);
  iVar5 = *(int *)(param_1 + 0x48);
  if (*(char *)(iVar1 + 0x2f5ec) != '\0') {
    ba_timeout_flush();
    uVar2 = _raw_spin_lock_irqsave(iVar6);
    if (((uVar7 & *(uint *)(param_1 + 0xc)) == 0) && ((uVar7 & *(uint *)(param_1 + 8)) == 0))
    goto LAB_001cb764;
    _raw_spin_unlock_irqrestore(iVar6,uVar2);
  }
  if ((*(uint *)(iVar1 + 0xa39f84) & 0x100) != 0) {
    uVar2 = _raw_spin_lock_irqsave(iVar6);
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~(uVar7 | 0x400000);
    _raw_spin_unlock_irqrestore(iVar6,uVar2);
    return;
  }
  uVar2 = _raw_spin_lock_irqsave(iVar6);
  uVar10 = *(uint *)(param_1 + 0xc);
  *(uint *)(param_1 + 0xc) = uVar10 & ~(uVar7 | 0x400000);
  _raw_spin_unlock_irqrestore(iVar6,uVar2);
  if (iVar5 != 0) {
    piVar4 = *(int **)(param_1 + 0x14);
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      if (*piVar4 == 4) {
        if (((uVar10 & piVar4[0x19]) != 0) || (DAT_005f48f1 != '\0')) {
          DAT_005f48f1 = (**(code **)(iVar8 + 0x1c))(iVar1,0);
          _LANCHOR1 = (**(code **)(iVar8 + 0x20))(iVar1,1);
          break;
        }
      }
      else if ((*piVar4 == 5) && (((uVar10 & piVar4[0x19]) != 0 || (_LANCHOR1 != '\0')))) {
        _LANCHOR1 = (**(code **)(iVar8 + 0x20))(iVar1,1);
        DAT_005f48f1 = (**(code **)(iVar8 + 0x1c))(iVar1,0);
        break;
      }
      piVar4 = piVar4 + 0x28;
    } while (iVar3 != iVar5);
  }
  uVar2 = _raw_spin_lock_irqsave(iVar6);
  if ((((uVar7 & *(uint *)(param_1 + 0xc)) == 0) && (DAT_005f48f1 == '\0')) && (_LANCHOR1 == '\0'))
  {
    mt_int_enable(iVar1,param_1,uVar7 | 0x400000);
  }
  else {
    (**(code **)(iVar9 + 0xc))(param_1 + 0xe0);
  }
LAB_001cb764:
  _raw_spin_unlock_irqrestore(iVar6,uVar2);
  return;
}

