// module: mt7915.ko
// function: ge_deq_req @ 0xd2754
// size: 908 bytes
//

undefined4 ge_deq_req(int param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  uint uVar5;
  byte bVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  
  if (*param_3 == '\0') {
    bVar6 = param_3[6];
    if (bVar6 < 4) {
      param_3[1] = bVar6;
      param_3[2] = bVar6;
    }
    else {
      param_3[2] = '\0';
      bVar6 = 3;
      param_3[1] = '\x03';
    }
    param_3[3] = bVar6;
    uVar2 = *(ushort *)(param_3 + 4);
    uVar8 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    uVar9 = (uint)*(ushort *)(param_3 + 4);
    if ((uVar2 < uVar8) && (uVar9 < 0x120)) {
      *(undefined4 *)(param_3 + 0x18) = param_2;
      param_3[0x28] = '\0';
      param_3[0x29] = '\0';
      param_3[0x2a] = '\0';
      param_3[0x2b] = '\0';
    }
    else {
      uVar4 = (undefined2)param_2;
      *(undefined2 *)(param_3 + 10) = uVar4;
      *(undefined2 *)(param_3 + 0xc) = uVar4;
      *(undefined2 *)(param_3 + 0xe) = uVar4;
      *(undefined2 *)(param_3 + 0x10) = uVar4;
    }
    *param_3 = '\x01';
  }
  else {
    uVar9 = (uint)*(ushort *)(param_3 + 4);
  }
  cVar1 = param_3[2];
  uVar8 = (uint)(byte)param_3[3];
  uVar5 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar9 < uVar5) {
    uVar2 = *(ushort *)(param_3 + 4);
    if (0x11f < uVar2) goto LAB_000d27a0;
    if (0 < *(int *)(param_3 + 0x18)) {
      uVar9 = (uint)(byte)param_3[6];
      if (uVar9 < 4) {
        uVar8 = uVar9;
        if (param_3[uVar9 + 0x28] != '\0') goto LAB_000d29dc;
      }
      else if ((int)cVar1 <= (int)uVar8) {
        do {
          if ((param_3[uVar8 + 0x28] == '\0') &&
             (*(int *)(param_1 + ((uint)uVar2 * 0x62 + uVar8) * 0x10 + 0x2f6cc) != 0)) break;
          uVar8 = uVar8 - 1 & 0xff;
        } while ((int)cVar1 <= (int)uVar8);
      }
      param_3[3] = (char)uVar8;
      *(ushort *)(param_3 + 8) = uVar2;
LAB_000d2864:
      if (DebugLevel < 4) goto LAB_000d2870;
      pcVar7 = "fail";
      if (*(int *)(param_3 + 0x24) == 0) {
        pcVar7 = "success";
      }
      goto LAB_000d2a30;
    }
LAB_000d29dc:
    param_3[0x24] = '\x01';
    param_3[0x25] = '\0';
    param_3[0x26] = '\0';
    param_3[0x27] = '\0';
    uVar8 = 0;
  }
  else {
LAB_000d27a0:
    for (; (int)cVar1 <= (int)uVar8; uVar8 = uVar8 - 1 & 0xff) {
      iVar10 = param_1 + uVar8 * 4 + 0x28633c;
      _raw_spin_lock_bh(iVar10);
      uVar2 = *(ushort *)(param_3 + uVar8 * 2 + 10);
      sVar3 = *(short *)(param_1 + (*(int *)(param_1 + uVar8 * 0x4018 + 0x28a350) + uVar8 * 0x200c +
                                   0x1431a4) * 2 + 4);
      _raw_spin_unlock_bh(iVar10);
      if (sVar3 == 0) {
        if (4 < DebugLevel) {
          printk("%s():tx_swq[%d] emtpy!\n","ge_deq_req",uVar8);
        }
        (param_3 + uVar8 * 2 + 10)[0] = '\0';
        (param_3 + uVar8 * 2 + 10)[1] = '\0';
      }
      else if (*(short *)(param_3 + uVar8 * 2 + 10) != 0) {
        param_3[3] = (char)uVar8;
        *(short *)(param_3 + 8) = sVar3;
        *(uint *)(param_3 + 0x18) = (uint)uVar2;
        if ((int)cVar1 <= (int)uVar8) goto LAB_000d2864;
        break;
      }
    }
    param_3[3] = (char)uVar8;
    param_3[0x24] = '\x01';
    param_3[0x25] = '\0';
    param_3[0x26] = '\0';
    param_3[0x27] = '\0';
  }
  if (DebugLevel < 4) {
LAB_000d2870:
    if (*(int *)(param_3 + 0x24) == 0) {
      return 1;
    }
    param_3[0x24] = '\x01';
    param_3[0x25] = '\0';
    param_3[0x26] = '\0';
    param_3[0x27] = '\0';
    return 1;
  }
  pcVar7 = "fail";
LAB_000d2a30:
  uVar5 = (uint)(byte)param_3[2];
  uVar9 = (uint)(byte)param_3[3];
  printk("%s(): DeqReq %s, Start/End/Cur Queue=%d/%d/%d\n","ge_deq_req",pcVar7,param_3[1],uVar5,
         uVar9);
  iVar10 = DebugLevel;
  if (*(int *)(param_3 + 0x24) == 0) {
    if (3 < DebugLevel) {
      printk("\tdeq_info=>wcid:%d, qidx:%d, pkt_cnt:%d, q_max_cnt=%d, QueuedNum=%d\n",
             (uint)*(ushort *)(param_3 + 8),(uint)(byte)param_3[3],*(undefined4 *)(param_3 + 0x18),
             *(undefined2 *)(param_3 + uVar8 * 2 + 10),
             *(undefined4 *)
              (param_1 + (uint)(byte)param_3[3] * 0x10 + (uint)*(ushort *)(param_3 + 8) * 0x620 +
              0x2f6cc));
    }
  }
  else {
    param_3[0x24] = '\x01';
    param_3[0x25] = '\0';
    param_3[0x26] = '\0';
    param_3[0x27] = '\0';
    if (3 < iVar10) {
      printk("\tdeq_info=>wcid:%d, qidx:%d, pkt_cnt:%d\n",*(undefined2 *)(param_3 + 8),param_3[3],
             *(undefined4 *)(param_3 + 0x18),uVar5,uVar9);
    }
  }
  return 1;
}

