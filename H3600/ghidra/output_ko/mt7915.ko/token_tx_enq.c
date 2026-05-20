// module: mt7915.ko
// function: token_tx_enq @ 0x1d3cc4
// size: 384 bytes
//

uint token_tx_enq(int *param_1,char *param_2,int param_3,undefined1 param_4,ushort param_5,
                 int param_6,int param_7)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  undefined2 extraout_r1;
  uint uVar4;
  char *pcVar5;
  int *piVar6;
  
  iVar3 = hc_get_chip_cap(param_1[0x29e5e8]);
  if (param_2 == (char *)0x0) {
    pcVar5 = &DAT_00000004;
    _raw_spin_lock_bh(4);
    uVar4 = 0;
  }
  else {
    pcVar5 = param_2 + 4;
    uVar4 = *(uint *)(param_2 + 0x14);
    _raw_spin_lock_bh(pcVar5);
    if (*param_2 == '\x01') {
      sVar1 = *(short *)(param_2 + 0xc);
      uVar4 = (uint)*(ushort *)(*(int *)(param_2 + 0x20) + sVar1 * 2);
      if (*(uint *)(param_2 + 0x10) < uVar4) {
        uVar4 = (uint)*(ushort *)(param_2 + 0x14);
      }
      else {
        if (param_2[1] == '\0') {
          piVar6 = (int *)(*(int *)(param_2 + 0x24) + uVar4 * 0x20);
        }
        else {
          piVar6 = (int *)(*(int *)(param_2 + 0x24) + (uVar4 - *(int *)(iVar3 + 0x14)) * 0x20);
        }
        if (*piVar6 != 0) {
          linux_pci_unmap_single(*(undefined4 *)(*param_1 + 0xc),piVar6[1],piVar6[2],0xff00);
          RTMPFreeNdisPacket(param_1,*piVar6);
        }
        *piVar6 = param_3;
        *(ushort *)(piVar6 + 3) = param_5;
        piVar6[1] = param_6;
        *(undefined1 *)((int)piVar6 + 0xe) = param_4;
        piVar6[2] = param_7;
        *(short *)(*(int *)(param_2 + 0x20) + sVar1 * 2) = (short)*(undefined4 *)(param_2 + 0x14);
        __aeabi_uidivmod(*(short *)(param_2 + 0xc) + 1,*(undefined4 *)(param_2 + 0x1c));
        piVar6 = (int *)(param_2 + 0x38);
        *(undefined2 *)(param_2 + 0xc) = extraout_r1;
        HintPreloadDataForWrite(piVar6);
        do {
          bVar2 = (bool)hasExclusiveAccess(piVar6);
        } while (!bVar2);
        *piVar6 = *piVar6 + -1;
        *(int *)(param_2 + 0x3c) = *(int *)(param_2 + 0x3c) + 1;
        *(short *)(param_1 + (uint)param_5 * 0x188 + 0xbf2e) =
             (short)param_1[(uint)param_5 * 0x188 + 0xbf2e] + 1;
      }
    }
    else {
      uVar4 = uVar4 & 0xffff;
    }
  }
  _raw_spin_unlock_bh(pcVar5);
  return uVar4;
}

