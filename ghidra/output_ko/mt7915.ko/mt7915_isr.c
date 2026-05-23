// module: mt7915.ko
// function: mt7915_isr @ 0x17d740
// size: 828 bytes
//

void mt7915_isr(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  uint local_30;
  uint local_2c;
  
  iVar8 = *(int *)(param_1 + 0xd0);
  local_30 = 0;
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(iVar8 + 0xb0));
  puVar6 = *(undefined4 **)(param_1 + 0x6c0);
  *(undefined1 *)(iVar8 + 0x90) = 0;
  mt_wlan_hook_call(8,iVar1,0);
  hif_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7010,&local_30);
  uVar2 = *(uint *)(iVar1 + 0xa39f84);
  if ((uVar2 & 0x10000000) == 0) {
    hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7010,local_30);
    return;
  }
  if (((uVar2 & 0x40) != 0) && ((local_30 & 0x8538007) == 0)) {
    hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7010);
    return;
  }
  if (local_30 == 0xffffffff) {
    *(uint *)(iVar1 + 0xa39f84) = uVar2 | 0x140;
    hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7010);
    return;
  }
  if ((local_30 & 0xa00000) != 0) {
    if (DebugLevel < 0) goto LAB_0017d7e0;
    printk(">>>TxCoherent<<<\n");
  }
  if (((local_30 & 0x500000) != 0) && (-1 < DebugLevel)) {
    printk(">>>RxCoherent<<<\n");
  }
LAB_0017d7e0:
  iVar7 = param_1 + 0xe0;
  uVar3 = _raw_spin_lock_irqsave(param_1 + 0xc0);
  if ((local_30 & 0xcc008000) != 0) {
    (*(code *)*puVar6)(iVar7);
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | local_30 & 0xcc008000;
  }
  if ((local_30 & 0x30000) != 0) {
    (*(code *)puVar6[1])(iVar7);
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | local_30 & 0x30000;
  }
  if ((local_30 & 7) != 0) {
    (*(code *)puVar6[2])(iVar7);
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | local_30 & 7;
    if ((((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar1 + 0xc) & 0xffff) == 0x7915) &&
        ((byte)"Get_RBIST_IQ_Data_Proc"[iVar1 + 0x10] == 0)) &&
       (iVar8 = *(int *)(iVar8 + 0xa4), iVar8 != 0)) {
      puVar5 = *(undefined4 **)(iVar8 + 0x6c0);
      local_2c = (uint)(byte)"Get_RBIST_IQ_Data_Proc"[iVar1 + 0x10];
      hif_io_read32(*(undefined4 *)(iVar1 + 0xa797a0),0xd9200);
      if ((local_2c & 0x80) != 0) {
        hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0xd9200,0x80);
        (*(code *)*puVar5)(iVar8 + 0xe0);
        uVar4 = _raw_spin_lock_irqsave(iVar8 + 0xc0);
        *(uint *)(iVar8 + 0xc) = *(uint *)(iVar8 + 0xc) | 0x80;
        _raw_spin_unlock_irqrestore(iVar8 + 0xc0,uVar4);
      }
    }
  }
  if ((local_30 & 0x10000000) != 0) {
    (*(code *)puVar6[6])(iVar7);
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x10000000;
  }
  if ((local_30 & 0x20000000) != 0) {
    (*(code *)puVar6[7])(iVar7);
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x20000000;
  }
  hif_io_write32(*(undefined4 *)(iVar1 + 0xa797a0),0xd7010,local_30);
  mt_int_disable(iVar1,param_1,local_30);
  _raw_spin_unlock_irqrestore(param_1 + 0xc0,uVar3);
  return;
}

