// module: mt7915.ko
// function: ge_rx_pkt_deq_tasklet @ 0x150808
// size: 4 bytes
//

void ge_rx_pkt_deq_tasklet(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined1 auStack_c0 [160];
  
  OS_SPIN_LOCK_BH(param_1 + 0x285bf0);
  if (*(int *)(param_1 + 0x285c0c) == 0) {
    *(undefined4 *)(param_1 + 0x285c04) = *(undefined4 *)(param_1 + 0x285bf4);
    *(undefined4 *)(param_1 + 0x285c08) = *(undefined4 *)(param_1 + 0x285bf8);
    *(undefined4 *)(param_1 + 0x285c0c) = *(undefined4 *)(param_1 + 0x285bfc);
  }
  else if (*(int *)(param_1 + 0x285bfc) != 0) {
    **(undefined4 **)(param_1 + 0x285c08) = *(undefined4 *)(param_1 + 0x285bf4);
    *(undefined4 *)(param_1 + 0x285c08) = *(undefined4 *)(param_1 + 0x285bf8);
    *(int *)(param_1 + 0x285c0c) = *(int *)(param_1 + 0x285bfc) + *(int *)(param_1 + 0x285c0c);
  }
  iVar3 = 0;
  *(undefined4 *)(param_1 + 0x285bf4) = 0;
  *(undefined4 *)(param_1 + 0x285bf8) = 0;
  *(undefined4 *)(param_1 + 0x285c10) = *(undefined4 *)(param_1 + 0x285c00);
  *(undefined4 *)(param_1 + 0x285bfc) = 0;
  OS_SPIN_UNLOCK_BH(param_1 + 0x285bf0);
  if (*(int *)(param_1 + 0x285c0c) != 0) {
    piVar2 = *(int **)(param_1 + 0x285c04);
    while (piVar2 != (int *)0x0) {
      iVar1 = *piVar2;
      *piVar2 = 0;
      *(int *)(param_1 + 0x285c04) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)(param_1 + 0x285c08) = 0;
      }
      *(int *)(param_1 + 0x285c0c) = *(int *)(param_1 + 0x285c0c) + -1;
      HintPreloadData(piVar2);
      os_zero_mem(auStack_c0,0x90);
      iVar3 = iVar3 + 1;
      asic_rx_pkt_process(param_1,0,auStack_c0,piVar2);
      if (*(int *)(param_1 + 0x285c0c) == 0 || iVar3 == 0x80) {
        return;
      }
      piVar2 = *(int **)(param_1 + 0x285c04);
    }
  }
  return;
}

