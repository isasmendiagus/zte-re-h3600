// module: mt7915.ko
// function: pci_rx_dma_done_rxq_handle @ 0x1cded0
// size: 400 bytes
//

undefined1 pci_rx_dma_done_rxq_handle(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  undefined1 local_2d;
  undefined4 local_2c [2];
  
  uVar6 = 0;
  local_2d = 0;
  iVar2 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar8 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  iVar5 = *(int *)("Get_RBIST_IQ_Data" + param_1 + 0x10);
  iVar7 = *(int *)(*(int *)(iVar2 + 4) + param_2 * 4);
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = *(ushort *)(iVar7 + 4);
  local_2c[0] = 0;
  _raw_spin_lock_bh(iVar7 + 0x54);
  while( true ) {
    if (((*(uint *)(param_1 + 0xa39f84) & 0x100) != 0) && (-1 < (int)*(uint *)(param_1 + 0xa39f84)))
    goto LAB_001cdfd0;
    iVar4 = IsStopingPdma(param_1 + 0xa7bf04);
    if (iVar4 != 0) goto LAB_001cdfd0;
    bVar9 = uVar1 < uVar6;
    uVar6 = uVar6 + 1;
    if (bVar9) break;
    iVar4 = (**(code **)(iVar2 + ((uint)*(byte *)(iVar7 + 0x1f) + (uint)*(byte *)(iVar7 + 0x1d) * 2)
                                 * 4 + 100))(param_1,&local_2d,local_2c,param_2);
    if (iVar4 == 0) goto LAB_001cdfd0;
    (**(code **)(iVar8 + 0x4c))(param_1);
  }
  local_2d = 1;
LAB_001cdfd0:
  if (*(short *)(iVar7 + 0x30) != 0) {
    hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar7 + 0x3c),
                   *(undefined4 *)(iVar7 + 0x34));
    *(undefined2 *)(iVar7 + 0x30) = 0;
    if (*(char *)(param_1 + 0x285bd8) == '\0') {
      (**(code **)(iVar5 + 8))(param_1,1);
    }
    else {
      smp_call_function_single
                (*(undefined1 *)(iVar3 + 0x1ec),RTMPRxDataDeqOffloadToOtherCPU,param_1);
    }
  }
  _raw_spin_unlock_bh(iVar7 + 0x54);
  return local_2d;
}

