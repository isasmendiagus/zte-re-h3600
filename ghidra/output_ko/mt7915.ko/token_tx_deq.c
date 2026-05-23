// module: mt7915.ko
// function: token_tx_deq @ 0x1d3af0
// size: 468 bytes
//

int token_tx_deq(int *param_1,char *param_2,uint param_3,undefined1 *param_4)

{
  ushort uVar1;
  bool bVar2;
  int iVar3;
  undefined2 extraout_r1;
  char *pcVar4;
  int *piVar5;
  undefined1 *puVar6;
  
  puVar6 = param_4;
  iVar3 = hc_get_chip_cap(param_1[0x29e5e8]);
  if (param_2 == (char *)0x0) {
    return 0;
  }
  pcVar4 = param_2 + 8;
  _raw_spin_lock_bh(pcVar4);
  if (*param_2 == '\x01') {
    if (param_3 <= *(uint *)(param_2 + 0x10)) {
      if (param_2[1] == '\0') {
        piVar5 = (int *)(*(int *)(param_2 + 0x24) + param_3 * 0x20);
      }
      else {
        piVar5 = (int *)(*(int *)(param_2 + 0x24) + (param_3 - *(int *)(iVar3 + 0x14)) * 0x20);
      }
      iVar3 = *piVar5;
      uVar1 = *(ushort *)(piVar5 + 3);
      *param_4 = *(undefined1 *)((int)piVar5 + 0xe);
      if (iVar3 == 0) {
        if (0 < DebugLevel) {
          printk("%s(): buggy here? token ID(%d) without pkt!\n","token_tx_deq",param_3,DebugLevel,
                 puVar6);
        }
        _raw_spin_unlock_bh(pcVar4);
        if (_LANCHOR1 != '\0') {
          return 0;
        }
        MtCmdFwLog2Host(param_1,1,2);
        _LANCHOR1 = 1;
        return 0;
      }
      *piVar5 = 0;
      linux_pci_unmap_single(*(undefined4 *)(*param_1 + 0xc),piVar5[1],piVar5[2],0xff00);
      *(undefined1 *)((int)piVar5 + 0xe) = 0;
      *(short *)(*(int *)(param_2 + 0x20) + *(short *)(param_2 + 0xe) * 2) = (short)param_3;
      __aeabi_uidivmod(*(short *)(param_2 + 0xe) + 1,*(undefined4 *)(param_2 + 0x1c));
      piVar5 = (int *)(param_2 + 0x38);
      *(undefined2 *)(param_2 + 0xe) = extraout_r1;
      HintPreloadDataForWrite(piVar5);
      do {
        bVar2 = (bool)hasExclusiveAccess(piVar5);
      } while (!bVar2);
      *piVar5 = *piVar5 + 1;
      *(int *)(param_2 + 0x40) = *(int *)(param_2 + 0x40) + 1;
      *(short *)(param_1 + (uint)uVar1 * 0x188 + 0xbf2e) =
           (short)param_1[(uint)uVar1 * 0x188 + 0xbf2e] + -1;
      goto LAB_001d3b3c;
    }
    if (0 < DebugLevel) {
      iVar3 = 0;
      printk("%s(): Invalid token ID(%d)\n","token_tx_deq",param_3,DebugLevel,puVar6);
      goto LAB_001d3b3c;
    }
  }
  iVar3 = 0;
LAB_001d3b3c:
  _raw_spin_unlock_bh(pcVar4);
  return iVar3;
}

