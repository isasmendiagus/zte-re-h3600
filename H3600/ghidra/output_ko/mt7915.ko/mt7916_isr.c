// module: mt7915.ko
// function: mt7916_isr @ 0x17da7c
// size: 520 bytes
//

void mt7916_isr(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  uint local_24;
  
  iVar5 = *(int *)(param_1 + 0xd0);
  local_24 = 0;
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(iVar5 + 0xb0));
  puVar4 = *(undefined4 **)(param_1 + 0x6c0);
  *(undefined1 *)(iVar5 + 0x90) = 0;
  hif_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7088,&local_24);
  uVar2 = *(uint *)(iVar1 + 0xa39f84);
  if ((uVar2 & 0x10000000) == 0) {
    hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7088,local_24);
    return;
  }
  if (((uVar2 & 0x40) != 0) && ((local_24 & 0x520004) == 0)) {
    hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7088);
    return;
  }
  if (local_24 == 0xffffffff) {
    *(uint *)(iVar1 + 0xa39f84) = uVar2 | 0x140;
    hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7088);
    return;
  }
  if ((local_24 & 0x900000) != 0) {
    if (DebugLevel < 0) goto LAB_0017db0c;
    printk(">>>TxCoherent<<<\n");
  }
  if (((local_24 & 0x500000) != 0) && (-1 < DebugLevel)) {
    printk(">>>RxCoherent<<<\n");
  }
LAB_0017db0c:
  iVar5 = param_1 + 0xe0;
  uVar3 = _raw_spin_lock_irqsave(param_1 + 0xc0);
  if ((local_24 & 0x80) != 0) {
    (*(code *)*puVar4)(iVar5);
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x80;
  }
  if ((local_24 & 0x20000) != 0) {
    (*(code *)puVar4[1])(iVar5);
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x20000;
  }
  if ((local_24 & 4) != 0) {
    (*(code *)puVar4[2])(iVar5);
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 4;
  }
  hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7088,local_24);
  mt_int_disable(iVar1,param_1,local_24);
  _raw_spin_unlock_irqrestore(param_1 + 0xc0,uVar3);
  return;
}

