// module: mt7915.ko
// function: pci_interrupt_enable @ 0x17cc98
// size: 360 bytes
//

void pci_interrupt_enable(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  uint local_2c [2];
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar5 = *(int *)(iVar1 + 0xa0);
  uVar2 = _raw_spin_lock_irqsave(param_1 + 0x285c50);
  hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0xd7010,0xffffffff);
  hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0xd7014,0);
  DataSynchronizationBarrier(0xf);
  if ((*(uint *)(*(int *)(iVar5 + 0xbc) + 0xd7090) & 0x7fffffff) != 0) {
    hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0xd7088,0xffffffff);
    hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0xd708c,0);
  }
  if (*(char *)(iVar1 + 0xa8) != '\0') {
    iVar3 = 0;
    do {
      puVar4 = *(uint **)(*(int *)(iVar1 + 0xac) + iVar3 * 4);
      iVar3 = iVar3 + 1;
      hif_io_read32(*(undefined4 *)(param_1 + 0xa797a0),puVar4[1],local_2c);
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),puVar4[1],local_2c[0] | *puVar4);
    } while (iVar3 < (int)(uint)*(byte *)(iVar1 + 0xa8));
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x74030188,0xff);
  DataSynchronizationBarrier(0xf);
  if ((*(uint *)(*(int *)(iVar5 + 0xbc) + 0xd7090) & 0x7fffffff) != 0) {
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x74020188,0xff);
  }
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x2000;
  _raw_spin_unlock_irqrestore(param_1 + 0x285c50,uVar2);
  return;
}

