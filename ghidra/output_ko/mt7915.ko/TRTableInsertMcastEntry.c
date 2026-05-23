// module: mt7915.ko
// function: TRTableInsertMcastEntry @ 0x148648
// size: 740 bytes
//

void TRTableInsertMcastEntry(int param_1,uint param_2,int param_3)

{
  undefined1 uVar1;
  byte bVar2;
  ushort uVar3;
  undefined2 uVar4;
  uint uVar5;
  int iVar6;
  undefined1 extraout_r1;
  char extraout_r1_00;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined2 *puVar9;
  char cVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  uVar5 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 < uVar5 && param_2 < 0x120) {
    iVar12 = param_1 + 0x1c0;
    iVar6 = param_2 * 0x620;
    if (iVar12 + iVar6 + 0x2f4e0 != 0) {
      iVar13 = param_1 + iVar6;
      *(undefined4 *)(iVar13 + 0x2f6a0) = 0x400;
      *(int *)(iVar13 + 0x2f6a4) = param_3;
      uVar1 = *(undefined1 *)(param_3 + 0xe);
      *(undefined1 *)(iVar13 + 0x2f763) = 0;
      iVar11 = iVar12 + iVar6 + 0x2f4e8;
      *(undefined1 *)(iVar13 + 0x2f761) = 0;
      *(undefined1 *)(iVar13 + 0x2f6aa) = uVar1;
      *(undefined1 *)(iVar13 + 0x2f762) = 1;
      puVar9 = (undefined2 *)(param_1 + iVar6 + 0x2f6b2);
      *(undefined1 *)(iVar13 + 0x2f766) = *(undefined1 *)(param_1 + 0x794cd5);
      uVar4 = BROADCAST_ADDR._4_2_;
      *(undefined4 *)(iVar11 + 3) = (undefined4)BROADCAST_ADDR;
      *(undefined2 *)(iVar11 + 7) = uVar4;
      *(short *)(iVar12 + iVar6 + 0x2f4e8) = (short)param_2;
      *(undefined2 *)(iVar12 + iVar6 + 0x2f4f2) = 0;
      do {
        puVar9 = puVar9 + 1;
        *puVar9 = 0;
      } while (puVar9 != (undefined2 *)(param_1 + iVar6 + 0x2f6c2));
      iVar11 = 0;
      puVar7 = (undefined4 *)(param_1 + iVar6 + 0x2f6c8);
      puVar8 = (undefined4 *)(param_1 + iVar6 + 0x2f730);
      do {
        iVar11 = iVar11 + 1;
        *puVar7 = 0;
        puVar7[-1] = 0;
        puVar7[1] = 0;
        puVar8 = puVar8 + 1;
        *puVar8 = 0;
        puVar7 = puVar7 + 4;
      } while (iVar11 != 4);
      iVar11 = param_1 + param_2 * 0x620;
      *(undefined4 *)(iVar11 + 0x2f708) = 0;
      *(undefined4 *)(iVar11 + 0x2f704) = 0;
      *(undefined4 *)(iVar11 + 0x2f70c) = 0;
      *(undefined4 *)(iVar11 + 0x2f744) = 0;
      *(undefined4 *)(iVar11 + 0x2f748) = 0;
      *(undefined4 *)(iVar11 + 0x2f74c) = 0;
      *(undefined4 *)(iVar11 + 0x2f750) = 0;
      *(undefined4 *)(iVar11 + 0x2f754) = 0;
      *(undefined1 *)(iVar11 + 0x2f758) = 1;
      *(undefined1 *)(iVar11 + 0x2f759) = 1;
      iVar6 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar6 == 2) {
        if (*(int *)(iVar11 + 0x2f6a4) == 0) {
          if (-1 < DebugLevel) {
            printk("%s: wdev == NULL\n","TRTableInsertMcastEntry");
          }
        }
        else {
          *(undefined1 *)(iVar11 + 0x2fa7d) = *(undefined1 *)(param_3 + 0x29);
        }
      }
      memmove((void *)(iVar12 + param_2 * 0x620 + 0x2f59a),(void *)(param_3 + 0x21),6);
      iVar6 = HcGetBandByWdev(param_3);
      if (*(char *)(param_1 + 0xa7a2e8) == '\0') {
        bVar2 = *(byte *)(param_3 + 0xe);
        __aeabi_idivmod((uint)bVar2,*(undefined2 *)(param_1 + 0xa7bec8));
        *(undefined1 *)(param_1 + (uint)bVar2 + 0xa7bea8) = extraout_r1;
      }
      else {
        bVar2 = *(byte *)(param_3 + 0xe);
        uVar3 = *(ushort *)(param_1 + 0xa7bec8) >> 1;
        __aeabi_idivmod((uint)bVar2,uVar3);
        if (iVar6 == 0) {
          cVar10 = '\0';
        }
        else {
          cVar10 = (char)uVar3;
        }
        *(char *)(param_1 + (uint)bVar2 + 0xa7bea8) = cVar10 + extraout_r1_00;
      }
      if (2 < DebugLevel) {
        printk("%s:band%u group_idx[%d]=%d\n","TRTableInsertMcastEntry",iVar6,
               (uint)*(byte *)(param_3 + 0xe),
               *(undefined1 *)(param_1 + (uint)*(byte *)(param_3 + 0xe) + 0xa7bea8));
      }
    }
  }
  return;
}

