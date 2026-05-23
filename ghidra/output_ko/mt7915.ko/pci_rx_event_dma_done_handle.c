// module: mt7915.ko
// function: pci_rx_event_dma_done_handle @ 0x1ca8a4
// size: 344 bytes
//

undefined1 pci_rx_event_dma_done_handle(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  undefined1 auStack_e0 [156];
  int local_44;
  int local_40;
  int local_3c;
  uint local_38;
  int local_34;
  undefined1 local_2d;
  undefined4 local_2c [2];
  
  local_44 = param_1 + 0xa70000;
  uVar2 = 0;
  local_2d = 0;
  local_3c = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  local_34 = param_1 + 0xa39000;
  iVar3 = *(int *)(*(int *)(local_3c + 4) + param_2 * 4);
  local_2c[0] = 0;
  local_40 = iVar3 + 0x54;
  local_38 = (uint)*(ushort *)(iVar3 + 4);
  _raw_spin_lock_bh(local_40);
  while( true ) {
    if (((*(uint *)(local_34 + 0xf84) & 0x100) != 0) && (-1 < (int)*(uint *)(local_34 + 0xf84)))
    goto LAB_001ca9b0;
    iVar1 = IsStopingPdma(param_1 + 0xa7bf04);
    if (iVar1 != 0) goto LAB_001ca9b0;
    bVar4 = local_38 < uVar2;
    uVar2 = uVar2 + 1;
    if (bVar4) break;
    iVar1 = (**(code **)(local_3c +
                         ((uint)*(byte *)(iVar3 + 0x1f) + (uint)*(byte *)(iVar3 + 0x1d) * 2) * 4 +
                        100))(param_1,&local_2d,local_2c,param_2);
    if (iVar1 == 0) goto LAB_001ca9b0;
    os_zero_mem(auStack_e0,0x90);
    asic_rx_pkt_process(param_1,param_2,auStack_e0,iVar1);
  }
  local_2d = 1;
LAB_001ca9b0:
  if (*(short *)(iVar3 + 0x30) != 0) {
    hif_io_write32(*(undefined4 *)(local_44 + 0x97a0),*(undefined4 *)(iVar3 + 0x3c),
                   *(undefined4 *)(iVar3 + 0x34));
    *(undefined2 *)(iVar3 + 0x30) = 0;
  }
  _raw_spin_unlock_bh(local_40);
  return local_2d;
}

