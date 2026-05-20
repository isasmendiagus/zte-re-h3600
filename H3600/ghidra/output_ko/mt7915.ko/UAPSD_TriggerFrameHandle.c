// module: mt7915.ko
// function: UAPSD_TriggerFrameHandle @ 0x1de83c
// size: 1996 bytes
//

/* WARNING: Removing unreachable block (ram,0x001de990) */
/* WARNING: Removing unreachable block (ram,0x001de9c4) */
/* WARNING: Removing unreachable block (ram,0x001de890) */
/* WARNING: Removing unreachable block (ram,0x001de960) */
/* WARNING: Removing unreachable block (ram,0x001ded38) */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void UAPSD_TriggerFrameHandle(int param_1,int param_2,uint param_3)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  char *pcVar10;
  uint uVar11;
  bool bVar12;
  int iVar13;
  uint local_78;
  short *local_74;
  uint *local_68;
  undefined4 local_4c;
  uint local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  uint local_38 [5];
  
  local_68 = local_38;
  local_48 = 0;
  uStack_44 = 1;
  uStack_40 = 2;
  local_3c = 3;
  local_38[0] = 0;
  local_38[1] = 2;
  local_38[2] = 4;
  local_38[3] = 6;
  local_4c = 0x3020100;
  _raw_spin_lock_bh("BssTableSortByRssi" + param_1 + 0x10);
  pcVar10 = "BssTableSortByRssi" + param_1 + 0x10;
  if (2 < DebugLevel) {
    printk("\nuapsd> bAPSDFlagLegacySent = %d!\n",*(undefined1 *)(param_2 + 0xb69));
  }
  iVar5 = DebugLevel;
  if (*(char *)(param_2 + 0xb63) == '\0') {
    iVar5 = *(int *)(param_2 + 0xb5c);
  }
  else {
    *(undefined4 *)(param_2 + 0xc7c) = 0;
    *(undefined4 *)(param_1 + (uint)*(ushort *)(param_2 + 0xe0) * 0x620 + 0x2f94c) = 0;
    if (iVar5 < 3) {
      if ((uint)(jiffies - *(int *)(param_2 + 0xb64)) < 10) goto LAB_001de980;
    }
    else {
      printk("uapsd> sorry! SP is not yet closed!\n");
      if ((uint)(jiffies - *(int *)(param_2 + 0xb64)) < 10) goto LAB_001de980;
      if (2 < DebugLevel) {
        printk(
              "uapsd> SP period is too large so SP is closed first! (%lu %lu %lu)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
              );
      }
    }
    gUAPSD_SP_CloseAbnormalNum = gUAPSD_SP_CloseAbnormalNum + 1;
    _raw_spin_unlock_bh();
    if ((param_2 != 0) && (*(char *)(param_2 + 0xaf8) == '\x01')) {
      FUN_001dda04(param_1,param_2);
    }
    _raw_spin_lock_bh(pcVar10);
    iVar5 = *(int *)(param_2 + 0xb5c);
  }
  if (iVar5 != 0) {
    if (2 < DebugLevel) {
      printk("uapsd> EOSP is not NULL!\n");
    }
LAB_001de980:
    _raw_spin_unlock_bh(pcVar10);
    return;
  }
  if (3 < *(byte *)(param_2 + 0xb15)) {
    if (2 < DebugLevel) {
      printk("uapsd> MaxSPLength >= 4 (%d)!\n");
    }
    *(undefined1 *)(param_2 + 0xb15) = 0;
  }
  *(int *)(param_2 + 0xb64) = jiffies;
  if (((*(ushort *)(param_2 + 0xbc) & 0xc03f) != 0) ||
     (*(undefined1 *)(param_2 + 0xb68) = 1, *(char *)(param_2 + 0xb16) == '\0')) {
    *(undefined1 *)(param_2 + 0xb68) = 0;
  }
  local_78 = param_3;
  if (7 < param_3) {
    local_78 = 1;
  }
  if (*(char *)(param_2 + (uint)*(byte *)((int)&WMM_UP2AC_MAP + local_78) + 0xb0d) == '\0')
  goto LAB_001de980;
  iVar13 = 0;
  uVar11 = 0;
  piVar8 = (int *)0x0;
  uVar4 = local_38[*(byte *)(param_2 + 0xb15)];
  iVar5 = param_1 + (uint)*(ushort *)(param_2 + 0xe0) * 0x620 + 0x2f6a0;
  do {
    local_68 = local_68 + -1;
    uVar6 = *local_68;
    if ((*(char *)(param_2 + uVar6 + 0xb11) != '\0') &&
       (iVar9 = param_2 + uVar6 * 0x10, *(int *)(iVar9 + 0xb18) != 0)) {
      bVar1 = *(byte *)((int)&local_4c + uVar6);
      uVar6 = uVar11;
      do {
        uVar11 = uVar6 + 1;
        if (uVar4 <= uVar6 && uVar4 != 0) {
          bVar12 = false;
          bVar3 = false;
          goto LAB_001dec18;
        }
        if (piVar8 == (int *)0x0) {
          piVar8 = *(int **)(iVar9 + 0xb18);
        }
        else {
          iVar7 = ge_enq_req(param_1,piVar8,(uint)bVar1,iVar5,0);
          if (iVar7 == 0) {
            RTMPFreeNdisPacket(param_1,piVar8);
            piVar8 = *(int **)(iVar9 + 0xb18);
            uVar11 = uVar6;
          }
          else {
            piVar8 = *(int **)(iVar9 + 0xb18);
          }
          if (piVar8 == (int *)0x0) break;
        }
        iVar7 = *piVar8;
        *piVar8 = 0;
        *(int *)(iVar9 + 0xb18) = iVar7;
        if (iVar7 == 0) {
          *(undefined4 *)(iVar9 + 0xb1c) = 0;
        }
        *(int *)(iVar9 + 0xb20) = *(int *)(iVar9 + 0xb20) + -1;
        *(undefined1 *)((int)piVar8 + 0x2f) = 1;
        *(undefined1 *)((int)piVar8 + 0x36) = 2;
        *(byte *)((int)piVar8 + 0x32) = ~((byte)~(byte)(((uint)bVar1 << 0x19) >> 0x18) >> 1);
        if ((*(byte *)((int)piVar8 + 0x3a) & 8) != 0) {
          iVar13 = 1;
        }
        uVar6 = uVar11;
      } while (*(int *)(iVar9 + 0xb18) != 0);
    }
  } while (local_68 != &local_48);
  bVar12 = true;
  bVar3 = false;
  uVar6 = uVar11;
  if (uVar11 != 0) {
    bVar3 = true;
  }
LAB_001dec18:
  if (iVar13 != 0) {
    *(undefined1 *)(param_2 + 0xb68) = 1;
  }
  iVar7 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  iVar9 = DebugLevel;
  if (iVar7 == 2) {
    *(undefined1 *)(param_2 + 0xb68) = 1;
  }
  iVar7 = jiffies;
  if (bVar3) {
    *(undefined1 *)((int)piVar8 + 0x2f) = 0;
  }
  *(undefined1 *)(param_2 + 0xb63) = 1;
  *(undefined1 *)(param_2 + 0xb62) = 0;
  if (2 < iVar9) {
    printk("uapsd> start a SP (Tx Num = %d) (Rough SP = %d) (Has Any Mgmt = %d) (Abnormal = %d) (Time = %lu)\n"
           ,uVar6,*(undefined1 *)(param_2 + 0xb68),iVar13,gUAPSD_SP_CloseAbnormalNum,iVar7);
  }
  if (uVar6 < 2) {
    bVar3 = false;
    *(undefined4 *)(param_2 + 0xb5c) = 0;
    *(undefined2 *)(param_2 + 0xb60) = 0;
    if (uVar6 == 0) {
      bVar3 = DebugLevel < 3;
      if (DebugLevel < 3) goto LAB_001decc4;
      printk("uapsd> No data, send a Qos-Null frame with ESOP bit on and UP=%d to end USP\n",
             local_78);
      bVar3 = true;
      piVar8 = *(int **)(param_2 + 0xb5c);
    }
    else {
      *(undefined1 *)((int)piVar8 + 0x33) = 1;
      *(undefined1 *)((int)piVar8 + 0x36) = 2;
      iVar5 = ge_enq_req(param_1,piVar8,*(byte *)((int)piVar8 + 0x32) & 0x7f,iVar5,0);
      if (iVar5 == 0) {
        RTMPFreeNdisPacket(param_1,piVar8);
        *(undefined1 *)(param_2 + 0xb62) = 0;
        *(undefined1 *)(param_2 + 0xb69) = 0;
        *(undefined1 *)(param_2 + 0xb63) = 0;
        (&DAT_0058000d)[param_1] = 0;
        goto LAB_001de980;
      }
      if (DebugLevel < 3) {
        piVar8 = *(int **)(param_2 + 0xb5c);
      }
      else {
        printk("uapsd> Only one packet with UP = %d\n",(int)*(char *)((int)piVar8 + 0x2a));
        piVar8 = *(int **)(param_2 + 0xb5c);
      }
    }
  }
  else {
    bVar3 = false;
    *(undefined1 *)((int)piVar8 + 0x33) = 1;
    *(undefined1 *)((int)piVar8 + 0x36) = 2;
    *(int **)(param_2 + 0xb5c) = piVar8;
    *(short *)(param_2 + 0xb60) = (short)uVar6 + -1;
  }
  if (((piVar8 != (int *)0x0) && ((*(byte *)((int)piVar8 + 0x3a) & 8) != 0)) && (2 < DebugLevel)) {
    printk("uapsd> The EOSP frame is a management frame.\n");
  }
LAB_001decc4:
  iVar5 = DebugLevel;
  local_74 = (short *)(param_2 + 0xb60);
  if (((*(char *)(param_2 + 0xb68) == '\0') && (*(char *)(param_2 + 0xb69) != '\0')) &&
     (*local_74 = *local_74 + 1, 2 < iVar5)) {
    printk("uapsd> A legacy PS is sent! UAPSDTxNum = %d\n");
  }
  uVar11 = (uint)*(ushort *)(param_2 + 0xf8);
  if (*(char *)(param_2 + 0xb16) != '\x01') {
    bVar12 = false;
  }
  uVar2 = *(ushort *)(param_2 + 0xe0);
  if ((bVar12) && (uVar4 = HcGetMaxStaNum(param_1), uVar2 < uVar4)) {
    iVar5 = (uint)*(byte *)(param_2 + 0xe4) * 0x5834 + param_1 + ((uVar11 << 0x15) >> 0x18);
    "vow_watf_q_lv1: %d\n"[iVar5 + 0x13] =
         "vow_watf_q_lv1: %d\n"[iVar5 + 0x13] & ~*(byte *)((int)&NUM_BIT8 + (uVar11 & 7));
  }
  *(undefined2 *)(param_2 + 0xb58) = 0;
  _raw_spin_unlock_bh(pcVar10);
  if ((bVar3) &&
     (RtmpEnqueueNullFrame
                (param_1,param_2 + 0xec,*(undefined1 *)(param_2 + 0xb7f),uVar11,
                 *(undefined1 *)(param_2 + 0xe4),1,1,local_78), 2 < DebugLevel)) {
    printk("uapsd> end a SP by a QoS Null frame!\n");
  }
  RTMPDeQueuePacket(param_1,0,4,*(undefined2 *)(param_2 + 0xe0),*local_74);
  return;
}

