// module: mt7915.ko
// function: pci_sys_init @ 0x1cada8
// size: 188 bytes
//

undefined4 pci_sys_init(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
  uVar1 = hc_get_hdev_privdata();
  iVar2 = hc_get_chip_ops(param_1);
  iVar3 = hc_get_hif_ctrl(param_1);
  iVar4 = hc_get_hdev_privdata(param_1);
  uVar5 = _raw_spin_lock_irqsave(iVar4 + 0x285c50);
  if (*(char *)(iVar3 + 0xa8) != '\0') {
    iVar7 = 0;
    do {
      iVar6 = *(int *)(*(int *)(iVar3 + 0xac) + iVar7 * 4);
      iVar7 = iVar7 + 1;
      *(undefined4 *)(iVar6 + 8) = 0;
      *(undefined4 *)(iVar6 + 0xc) = 0;
    } while (iVar7 < (int)(uint)*(byte *)(iVar3 + 0xa8));
  }
  _raw_spin_unlock_irqrestore(iVar4 + 0x285c50,uVar5);
  if (*(code **)(iVar2 + 0x1c8) != (code *)0x0) {
    (**(code **)(iVar2 + 0x1c8))(iVar4);
  }
  chip_init_hif_dma(uVar1);
  asic_init_txrx_ring(uVar1);
  chip_init_dmasch(uVar1);
  return 0;
}

