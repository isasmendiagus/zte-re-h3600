// module: mt7915.ko
// function: ge_qm_exit @ 0xd1c2c
// size: 260 bytes
//

void ge_qm_exit(int param_1)

{
  int iVar1;
  int *piVar2;
  undefined1 auStack_19 [5];
  
  RTMPReleaseTimer(param_1 + 0x285c18,auStack_19);
  _raw_spin_lock_bh(param_1 + 0x285b3c);
  piVar2 = *(int **)(param_1 + 0x285b4c);
  while (piVar2 != (int *)0x0) {
    iVar1 = *piVar2;
    *piVar2 = 0;
    *(int *)(param_1 + 0x285b4c) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x285b50) = 0;
    }
    *(int *)(param_1 + 0x285b54) = *(int *)(param_1 + 0x285b54) + -1;
    RTMPFreeNdisPacket(param_1,piVar2);
    piVar2 = *(int **)(param_1 + 0x285b4c);
  }
  _raw_spin_unlock_bh(param_1 + 0x285b3c);
  _raw_spin_lock_bh(param_1 + 0x285b98);
  piVar2 = *(int **)(param_1 + 0x285b9c);
  while (piVar2 != (int *)0x0) {
    iVar1 = *piVar2;
    *piVar2 = 0;
    *(int *)(param_1 + 0x285b9c) = iVar1;
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x285ba0) = 0;
    }
    *(int *)(param_1 + 0x285ba4) = *(int *)(param_1 + 0x285ba4) + -1;
    RTMPFreeNdisPacket(param_1,piVar2);
    piVar2 = *(int **)(param_1 + 0x285b9c);
  }
  _raw_spin_unlock_bh(param_1 + 0x285b98);
  ge_sta_clean_queue(param_1,0x7fff);
  return;
}

