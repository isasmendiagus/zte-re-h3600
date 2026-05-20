// module: mt7915.ko
// function: sta_ieee_802_11_data_rx @ 0x53760
// size: 1616 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 sta_ieee_802_11_data_rx(int param_1,int param_2,int param_3,int *param_4)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  code *pcVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  bool bVar11;
  
  pbVar10 = *(byte **)(param_3 + 0x10);
  pbVar9 = *(byte **)(param_3 + 0x1c);
  iVar7 = *(int *)(param_2 + 0x904);
  iVar3 = GetStaCfgByWdev();
  uVar1 = *(undefined1 *)(param_2 + 0xc);
  if (3 < DebugLevel) {
    uVar8 = *(uint *)(param_3 + 0x44);
    printk("%s(): wcid=%d, wdev_idx=%d, pRxBlk->Flags=0x%x, fRX_AP/STA/ADHOC=0x%x/0x%x/0x%x, Type/SubType=%d/%d, FrmDS/ToDS=%d/%d\n"
           ,"sta_ieee_802_11_data_rx",(short)param_4[0x38],uVar1,uVar8,uVar8 & 0x100,uVar8 & 0x200,
           uVar8 & 0x400,((uint)*pbVar9 << 0x1c) >> 0x1e,*pbVar9 >> 4,
           ((uint)pbVar9[1] << 0x1e) >> 0x1f,pbVar9[1] & 1);
  }
  pcVar6 = *(code **)(iVar7 + 0x68);
  if (pcVar6 != (code *)0x0) {
    (*pcVar6)(param_1,param_2,param_3);
  }
  param_4[0x2ba] = 0;
  *(undefined4 *)(param_1 + (uint)*(ushort *)(param_4 + 0x38) * 0x620 + 0x2f954) = 0;
  iVar7 = *(int *)(param_3 + 0x1c);
  *(short *)(param_3 + 0x40) = *(short *)(param_3 + 0x40) + -0x18;
  if ((((uint)*pbVar9 << 0x18) >> 0x1c & 8) == 0) {
    iVar7 = iVar7 + 0x18;
    uVar8 = 0;
  }
  else {
    uVar8 = *(byte *)(iVar7 + 0x18) & 0xf;
    if ((*(short *)(param_1 + ((uint)*(ushort *)(param_3 + 0x4e) * 0xa60 +
                               (uint)*(byte *)(param_3 + 0x53) + 0x514f8) * 2 + 4) == 0) ||
       ((*pbVar10 & 0x10) == 0)) {
      *pbVar10 = *pbVar10 & 0xfe;
      cVar2 = *(char *)(iVar7 + 0x18);
    }
    else {
      *pbVar10 = *pbVar10 | 1;
      cVar2 = *(char *)(iVar7 + 0x18);
    }
    if (cVar2 < '\0') {
      *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 2;
      *(int *)(param_1 + 0xa39ee0) = *(int *)(param_1 + 0xa39ee0) + 1;
    }
    if ((*pbVar10 & 1) != 0) {
      *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 1;
      *(int *)(param_1 + 0xa39f00) = *(int *)(param_1 + 0xa39f00) + 1;
    }
    iVar7 = iVar7 + 0x1a;
    *(short *)(param_3 + 0x40) = *(short *)(param_3 + 0x40) + -2;
  }
  *(char *)(param_3 + 0x4a) = (char)uVar8;
  iVar4 = rx_chk_duplicate_frame(param_1,param_3,param_2);
  if (iVar4 == 1) {
    if (2 < DebugLevel) {
      printk("%s(): duplicate frame drop it!\n","sta_ieee_802_11_data_rx");
    }
    return 0;
  }
  if ((*param_4 == 2) && ((*pbVar10 & 0x10) != 0)) {
    iVar4 = RtmpPktPmBitCheck(param_1,iVar3);
    bVar5 = pbVar9[1];
    if (((iVar4 == 1) && ((bVar5 & 0x20) != 0)) &&
       (((((uVar8 == 0 || uVar8 == 3 && (*(char *)(param_1 + 0x794ca7) == '\0')) ||
          ((uVar8 - 1 < 2 && (*(char *)(param_1 + 0x794ca8) == '\0')))) ||
         ((uVar8 - 4 < 2 && (*(char *)(param_1 + 0x794ca9) == '\0')))) ||
        ((uVar8 - 6 < 2 && (*(char *)(param_1 + 0x794caa) == '\0')))))) {
      hif_ps_poll_enq(param_1,iVar3);
      bVar5 = pbVar9[1];
    }
  }
  else {
    bVar5 = pbVar9[1];
  }
  if ((bVar5 & 0x80) != 0) {
    if ((*(byte *)(param_3 + 99) < 0x40) && ((param_4[0x2d] & 2U) != 0)) {
      *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 4;
    }
    else {
      iVar7 = iVar7 + 4;
      *(short *)(param_3 + 0x40) = *(short *)(param_3 + 0x40) + -4;
    }
  }
  iVar4 = DebugLevel;
  if ((*pbVar9 & 0x40) != 0) {
    if (DebugLevel < 4) {
      return 0;
    }
    printk("%s(): Null/QosNull frame!\n","sta_ieee_802_11_data_rx");
    return 0;
  }
  bVar11 = (pbVar10[1] & 0x40) != 0;
  if (bVar11) {
    iVar7 = iVar7 + 2;
  }
  *(int *)(param_3 + 0x3c) = iVar7;
  if (bVar11) {
    *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 0x10;
  }
  param_4[0x2ba] = 0;
  *(undefined4 *)(param_1 + (uint)*(ushort *)(param_4 + 0x38) * 0x620 + 0x2f954) = 0;
  if (3 < iVar4) {
    uVar8 = *(uint *)(param_3 + 0x44);
    printk("%s():pRxInfo->Bcast =%d, pRxInfo->Mcast=%d, pRxBlk->Flags=0x%x, fRX_AP/STA/ADHOC=0x%x/0x%x/0x%x\n"
           ,"sta_ieee_802_11_data_rx",((uint)*pbVar10 << 0x19) >> 0x1f,
           ((uint)*pbVar10 << 0x1a) >> 0x1f,uVar8,uVar8 & 0x100,uVar8 & 0x200,uVar8 & 0x400);
  }
  if ((*pbVar10 & 0x60) != 0) {
    if ((pbVar9[1] & 4) == 0) {
      if (((pbVar9[1] & 2) == 0) ||
         (iVar3 = memcmp(*(void **)(param_3 + 0x30),(void *)(param_2 + 0x1b),6), iVar3 != 0)) {
        uVar8 = *(uint *)(param_1 + 0xa39c50);
        *(uint *)(param_1 + 0xa39c50) = uVar8 + 1;
        *(uint *)(param_1 + 0xa39c54) = *(int *)(param_1 + 0xa39c54) + (uint)(0xfffffffe < uVar8);
        indicate_802_11_pkt(param_1,param_3,uVar1);
        return 1;
      }
      if (3 < DebugLevel) {
        printk("%s(): pFmeCtrl->FrDs!\n","sta_ieee_802_11_data_rx");
      }
    }
    else if (3 < DebugLevel) {
      printk("%s(): MoreFrag!\n","sta_ieee_802_11_data_rx");
    }
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
    return 1;
  }
  if ((*pbVar10 & 0x10) != 0) {
    *(int *)(param_1 + 0xa39e28) = *(int *)(param_1 + 0xa39e28) + 1;
    if ((iVar3 != 0) && (*(ushort *)(iVar3 + 0x2124a4) < 2)) {
      *(undefined2 *)(iVar3 + 0x2124a4) = 2;
    }
    param_4[0x4e] = (uint)*(ushort *)(param_3 + 0x62);
    if ((*(byte *)(param_3 + 99) & 2) == 0) {
      param_4[0x31d] = param_4[0x31d] + 1;
    }
    else {
      param_4[0x31e] = param_4[0x31e] + 1;
    }
  }
  *(undefined1 *)(param_2 + 0x908) = *(undefined1 *)(param_3 + 0x5c);
  *(undefined1 *)(param_2 + 0x909) = *(undefined1 *)(param_3 + 0x5d);
  *(short *)(param_4 + 0x5d) = (short)*(char *)(param_3 + 0x60);
  *(undefined2 *)((int)param_4 + 0x176) = 1;
  if ((*(char *)(param_3 + 0x22) == '\0') && ((pbVar9[1] & 4) == 0)) {
    iVar3 = *(int *)(param_3 + 0x38);
  }
  else {
    de_fragment_data_pkt(param_1,param_3);
    if (*(int *)(param_3 + 0x38) == 0) {
      return 1;
    }
    if (((pbVar9[1] & 0x40) == 0) || ((param_4[0xb1] & 0x10U) == 0)) goto LAB_00053a1c;
    *(short *)(param_3 + 0x40) = *(short *)(param_3 + 0x40) + -8;
    iVar3 = rtmp_chk_tkip_mic(param_1,param_4,param_3);
  }
  if (iVar3 == 0) {
    return 1;
  }
LAB_00053a1c:
  *(uint *)(param_1 + 0xa78a1c) = (uint)*(ushort *)(param_3 + 0x48) + *(int *)(param_1 + 0xa78a1c);
  if (*param_4 == 2) {
    *(undefined2 *)(*(int *)(param_3 + 0x38) + 0x42) = *(undefined2 *)(param_3 + 0x4e);
  }
  if ((*(uint *)(param_3 + 0x44) & 0x40000) != 0) {
    rx_802_3_data_frm_announce(param_1,param_4,param_3,param_2);
    return 1;
  }
  rx_data_frm_announce();
  return 1;
}

