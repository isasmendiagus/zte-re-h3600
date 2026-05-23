// module: mt7915.ko
// function: dev_rx_ctrl_frm @ 0xcac5c
// size: 1524 bytes
//

void dev_rx_ctrl_frm(int param_1,int param_2)

{
  ushort uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  undefined2 uVar5;
  uint uVar6;
  byte *pbVar7;
  undefined4 uVar8;
  int iVar9;
  ushort uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  undefined1 *puVar18;
  undefined1 *puVar19;
  int local_24 [2];
  
  pbVar7 = *(byte **)(param_2 + 0x1c);
  iVar9 = *(int *)(param_2 + 0x38);
  switch(*pbVar7 >> 4) {
  case 2:
LAB_000cafe8:
    if (3 < DebugLevel) {
      puVar19 = *(undefined1 **)(param_2 + 0x28);
      puVar18 = *(undefined1 **)(param_2 + 0x2c);
      printk("%s():Recive TRIG frame . A1:%02x:%02x:%02x:%02x:%02x:%02x,A2:%02x:%02x:%02x:%02x:%02x:%02x\n\r"
             ,"dev_rx_ctrl_frm",*puVar19,puVar19[1],puVar19[2],puVar19[3],puVar19[4],puVar19[5],
             *puVar18,puVar18[1],puVar18[2],puVar18[3],puVar18[4],puVar18[5]);
    }
    break;
  default:
    goto switchD_000cac84_caseD_3;
  case 8:
    iVar3 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if ((iVar3 == 2) &&
       (uVar10 = *(ushort *)(param_2 + 0x4e),
       uVar4 = hc_get_chip_wtbl_no_matched_idx(*(undefined4 *)(param_1 + 0xa797a0)), uVar10 == uVar4
       )) {
      piVar2 = (int *)MacTableLookup(param_1,*(undefined4 *)(param_2 + 0x2c));
      if (piVar2 == (int *)0x0) {
        if (-1 < DebugLevel) {
          puVar19 = *(undefined1 **)(param_2 + 0x28);
          puVar18 = *(undefined1 **)(param_2 + 0x2c);
          printk("%s():pEntry(NULL),Cannot found WCID of BAR packet!A1:%02x:%02x:%02x:%02x:%02x:%02x,A2:%02x:%02x:%02x:%02x:%02x:%02x\n"
                 ,"dev_rx_ctrl_frm",*puVar19,puVar19[1],puVar19[2],puVar19[3],puVar19[4],puVar19[5],
                 *puVar18,puVar18[1],puVar18[2],puVar18[3],puVar18[4],puVar18[5]);
        }
        goto LAB_000cb08c;
      }
      uVar5 = (undefined2)piVar2[0x38];
      *(undefined2 *)(param_2 + 0x4e) = uVar5;
      if (((&DAT_0036790d)[param_1] == '\x01') && (*piVar2 == 0x40001 || *piVar2 == 2)) {
        iVar3 = RTMPLookupRepeaterCliEntry(param_1,0,*(undefined4 *)(param_2 + 0x28));
        if (iVar3 == 0) {
          if (*piVar2 == 2) {
            *(undefined2 *)(param_2 + 0x4e) =
                 *(undefined2 *)
                  ((uint)*(ushort *)
                          (&DAT_00580e38 + (uint)*(byte *)(piVar2 + 0x39) * 0x2137b0 + param_1) *
                   0x14c0 + param_1 + 0xa1e00);
            goto LAB_000cb1d8;
          }
        }
        else if (*(char *)(iVar3 + 1) == '\x01') {
          *(undefined2 *)(param_2 + 0x4e) = *(undefined2 *)(*(int *)(iVar3 + 0x4144) + 0xe0);
LAB_000cb1d8:
          if (DebugLevel < 3) goto LAB_000cb08c;
          puVar18 = *(undefined1 **)(param_2 + 0x28);
          printk("%s():%02x:%02x:%02x:%02x:%02x:%02x recv BAR\n\r","dev_rx_ctrl_frm",*puVar18,
                 puVar18[1],puVar18[2],puVar18[3],puVar18[4],puVar18[5]);
          uVar5 = *(undefined2 *)(param_2 + 0x4e);
          goto LAB_000cb090;
        }
        if (-1 < DebugLevel) {
          puVar19 = *(undefined1 **)(param_2 + 0x28);
          puVar18 = *(undefined1 **)(param_2 + 0x2c);
          printk("%s():Cannot found WCID of BAR packet!. A1:%02x:%02x:%02x:%02x:%02x:%02x,A2:%02x:%02x:%02x:%02x:%02x:%02x\n\r"
                 ,"dev_rx_ctrl_frm",*puVar19,puVar19[1],puVar19[2],puVar19[3],puVar19[4],puVar19[5],
                 *puVar18,puVar18[1],puVar18[2],puVar18[3],puVar18[4],puVar18[5]);
        }
        goto switchD_000cac84_caseD_3;
      }
    }
    else {
LAB_000cb08c:
      uVar5 = *(undefined2 *)(param_2 + 0x4e);
    }
LAB_000cb090:
    bar_process(param_1,uVar5,*(undefined2 *)(param_2 + 0x48),pbVar7);
    if ((pbVar7[0x10] & 4) == 0) {
      ba_rec_session_tear_down(param_1,*(undefined2 *)(param_2 + 0x4e),pbVar7[0x11] >> 4);
    }
    goto switchD_000cac84_caseD_3;
  case 9:
    if (3 < DebugLevel) {
      printk("%s():BlockAck From WCID:%d\n","dev_rx_ctrl_frm",*(undefined2 *)(param_2 + 0x4e));
      iVar3 = *(int *)(param_2 + 0x1c);
      if (3 < DebugLevel) {
        uVar4 = (uint)*(byte *)(iVar3 + 8);
        uVar11 = (uint)*(byte *)(iVar3 + 9);
        uVar12 = (uint)*(byte *)(iVar3 + 10);
        uVar13 = (uint)*(byte *)(iVar3 + 0xb);
        uVar14 = (uint)*(byte *)(iVar3 + 0xc);
        uVar15 = (uint)*(byte *)(iVar3 + 0xd);
        uVar16 = (uint)*(byte *)(iVar3 + 0xe);
        uVar17 = (uint)*(byte *)(iVar3 + 0xf);
        printk("\tRA=%02x:%02x:%02x:%02x:%02x:%02x, TA=%02x:%02x:%02x:%02x:%02x:%02x\n",
               *(undefined1 *)(iVar3 + 4),*(undefined1 *)(iVar3 + 5),*(undefined1 *)(iVar3 + 6),
               *(undefined1 *)(iVar3 + 7),uVar4,uVar11,uVar12,uVar13,uVar14,uVar15,uVar16,uVar17);
        if (DebugLevel < 4) break;
        uVar6 = (uint)*(byte *)(iVar3 + 0x10);
        printk("\tBA Control: AckPolicy=%d, MTID=%d, Compressed=%d, TID_INFO=0x%x\n",uVar6 & 1,
               (uVar6 << 0x1e) >> 0x1f,(uVar6 << 0x1d) >> 0x1f,*(byte *)(iVar3 + 0x11) >> 4,uVar4,
               uVar11,uVar12,uVar13,uVar14,uVar15,uVar16,uVar17);
      }
      if ((*(byte *)(iVar3 + 0x10) & 5) == 4) {
        if ((DebugLevel < 4) ||
           (printk("\tBA StartingSeqCtrl:StartSeq=%d, FragNum=%d\n",
                   (uint)*(byte *)(iVar3 + 0x13) << 4 | (uint)(*(byte *)(iVar3 + 0x12) >> 4),
                   *(byte *)(iVar3 + 0x12) & 0xf), DebugLevel < 4)) break;
        printk("\tBA Bitmap:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(iVar3 + 0x14)
               ,*(undefined1 *)(iVar3 + 0x15),*(undefined1 *)(iVar3 + 0x16),
               *(undefined1 *)(iVar3 + 0x17),*(undefined1 *)(iVar3 + 0x18),
               *(undefined1 *)(iVar3 + 0x19),*(undefined1 *)(iVar3 + 0x1a),
               *(undefined1 *)(iVar3 + 0x1b));
      }
      goto LAB_000cafe8;
    }
    break;
  case 10:
    uVar10 = *(ushort *)(param_2 + 0x20);
    uVar8 = *(undefined4 *)(param_2 + 0x2c);
    iVar3 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if ((iVar3 == 2) &&
       (uVar1 = *(ushort *)(param_2 + 0x4e),
       uVar4 = hc_get_chip_wtbl_no_matched_idx(*(undefined4 *)(param_1 + 0xa797a0)), uVar1 == uVar4)
       ) {
      iVar3 = *(int *)(param_1 + (uint)*(byte *)(iVar9 + 0x2d) * 4 + 0xc);
      (**(code **)(*(int *)(iVar3 + 0x904) + 0xb8))
                (param_1,*(undefined4 *)(param_2 + 0x2c),iVar3,local_24);
      if (local_24[0] == 0) {
        if (1 < DebugLevel) {
          printk("%s(): Cannot found WCID of PS-Poll packet!\n","dev_rx_ctrl_frm");
        }
        goto LAB_000cae00;
      }
      uVar1 = *(ushort *)(local_24[0] + 0xe0);
      *(ushort *)(param_2 + 0x4e) = uVar1;
    }
    else {
LAB_000cae00:
      uVar1 = *(ushort *)(param_2 + 0x4e);
    }
    uVar4 = HcGetMaxStaNum(param_1);
    if (uVar1 < uVar4) {
      uVar10 = uVar10 & 0x3fff;
      iVar3 = (uint)*(ushort *)(param_2 + 0x4e) * 0x14c0;
      local_24[0] = param_1 + iVar3 + 0xa1d20;
      if (*(ushort *)(param_1 + iVar3 + 0xa1e18) == uVar10) {
        RtmpHandleRxPsPoll(param_1,uVar8,(uint)*(ushort *)(param_2 + 0x4e),0);
      }
      else if (-1 < DebugLevel) {
        printk("%s(): Aid mismatch(pkt:%d, Entry:%d)!\n","dev_rx_ctrl_frm",uVar10);
      }
    }
    goto switchD_000cac84_caseD_3;
  }
  dbg_log_wrapper(param_1,0x13,pbVar7,*(undefined2 *)(param_2 + 0x48));
switchD_000cac84_caseD_3:
  RTMPFreeNdisPacket(param_1,iVar9);
  return;
}

