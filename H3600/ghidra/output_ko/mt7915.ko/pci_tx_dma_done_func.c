// module: mt7915.ko
// function: pci_tx_dma_done_func @ 0x1cb830
// size: 340 bytes
//

void pci_tx_dma_done_func(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  int iVar9;
  byte *pbVar10;
  
  iVar5 = *(int *)(param_1 + 0xd0);
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(iVar5 + 0xb0));
  puVar4 = *(undefined4 **)(param_1 + 0x6c0);
  uVar6 = *(uint *)(param_1 + 0x1c);
  iVar9 = *(int *)(param_1 + 0x20);
  if (((*(uint *)(iVar1 + 0xa39f84) & 0x140) != 0) ||
     (iVar2 = IsStopingPdma(iVar1 + 0xa7bf04), iVar2 != 0)) {
    uVar3 = _raw_spin_lock_irqsave(param_1 + 0xc0);
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~uVar6;
    _raw_spin_unlock_irqrestore(param_1 + 0xc0,uVar3);
    return;
  }
  iVar2 = param_1 + 0xc0;
  uVar3 = _raw_spin_lock_irqsave(iVar2);
  uVar7 = *(uint *)(param_1 + 0xc);
  *(uint *)(param_1 + 0xc) = uVar7 & ~uVar6;
  _raw_spin_unlock_irqrestore(iVar2,uVar3);
  if (iVar9 != 0) {
    pbVar8 = (byte *)(param_1 + 0x23);
    pbVar10 = (byte *)(iVar9 + 0x23 + param_1);
    do {
      while( true ) {
        pbVar8 = pbVar8 + 1;
        iVar9 = *(int *)(param_1 + 0x18) + (uint)*pbVar8 * 0x60;
        if ((uVar7 & *(uint *)(iVar9 + 0x54)) == 0) break;
        (**(code **)(iVar5 + *(int *)(*(int *)(param_1 + 0x18) + (uint)*pbVar8 * 0x60) * 4 + 0xc))
                  (iVar1,*(undefined1 *)(iVar9 + 0x58));
        if (pbVar8 == pbVar10) goto LAB_001cb908;
      }
    } while (pbVar8 != pbVar10);
  }
LAB_001cb908:
  uVar3 = _raw_spin_lock_irqsave(iVar2);
  if ((uVar6 & *(uint *)(param_1 + 0xc)) == 0) {
    mt_int_enable(iVar1,param_1,uVar6);
  }
  else {
    (*(code *)*puVar4)(param_1 + 0xe0);
  }
  _raw_spin_unlock_irqrestore(iVar2,uVar3);
  return;
}

