// module: mt7915.ko
// function: LinkUp @ 0x71e1c
// size: 2488 bytes
//

void LinkUp(int param_1,int param_2,undefined4 *param_3,undefined4 param_4,undefined4 param_5)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  char *pcVar10;
  void *__src;
  undefined4 *__src_00;
  int iVar11;
  uint uVar12;
  uint uVar13;
  undefined1 uStack_49;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  iVar6 = GetStaCfgByWdev(param_1,param_3);
  if (iVar6 == 0) {
    printk(&_LC1,0xb92);
    dump_stack();
    return;
  }
  if (param_3 == (undefined4 *)0x0) {
    return;
  }
  iVar11 = param_3[0xff9];
  if (iVar11 == 0) {
    return;
  }
  *(undefined4 *)(iVar6 + 0x212460) = 0x32;
  *(undefined1 *)(param_3 + 0x2ed) = 0;
  *(undefined1 *)(iVar6 + 0x212808) = 1;
  *(undefined1 *)(iVar6 + 0x213172) = 0;
  *(undefined2 *)(iVar6 + 0x2124a4) = 10;
  if (param_3[5] == 0x100) {
    iVar7 = *(int *)(param_3[1] + 0x4144);
  }
  else {
    iVar7 = GetAssociatedAPByWdev(param_1,param_3);
  }
  if (iVar7 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s:wdev(type=%d,func_idx=%d),pEntry=NULL,return!\n","LinkUp",param_3[5],
           *(undefined1 *)((int)param_3 + 0xe));
    return;
  }
  wlan_operate_get_addht(param_3);
  RTMPCancelTimer(BN_mod_sqr + iVar6,&uStack_49);
  bVar1 = *(byte *)(iVar6 + 0x212426);
  __src = (void *)(iVar6 + 0x212406);
  memmove(&local_48,__src,(uint)bVar1);
  __memzero(__src,0x20);
  *(byte *)(iVar6 + 0x212426) = *(byte *)(iVar6 + 0x4139);
  memmove(__src,(void *)(iVar6 + 0x4119),(uint)*(byte *)(iVar6 + 0x4139));
  __src_00 = (undefined4 *)(iVar6 + 0x212428);
  *(undefined4 *)(iVar6 + 0x212428) = *(undefined4 *)(iVar6 + 0x413a);
  *(undefined2 *)(iVar6 + 0x21242c) = *(undefined2 *)(iVar6 + 0x413e);
  *(undefined1 *)(iVar6 + 0x1a) = *(undefined1 *)(iVar6 + 0x4165);
  *(undefined2 *)(iVar6 + 0x40b0) = *(undefined2 *)(iVar6 + 0x416a);
  *(undefined2 *)(iVar6 + 0x40b2) = *(undefined2 *)(iVar6 + 0x4174);
  *(undefined2 *)(iVar6 + 0x40b4) = *(undefined2 *)(iVar6 + 0x416c);
  *(undefined4 *)(iVar6 + 0x40b6) = *(undefined4 *)(iVar6 + 0x41c0);
  *(undefined4 *)(iVar6 + 0x40ba) = *(undefined4 *)(iVar6 + 0x41c4);
  *(undefined2 *)(iVar6 + 0x40be) = *(undefined2 *)(iVar6 + 0x41c8);
  *(undefined1 *)(iVar6 + 0x40c0) = *(undefined1 *)(iVar6 + 0x41ca);
  *(undefined2 *)(&DAT_00794c50 + param_1) = *(undefined2 *)(iVar6 + 0x416e);
  *(undefined2 *)(iVar6 + 0x40c4) = *(undefined2 *)(iVar6 + 0x4172);
  *(undefined2 *)(iVar6 + 0x40c2) = *(undefined2 *)(iVar6 + 0x4170);
  *(byte *)(iVar6 + 0x40c6) = *(byte *)(iVar6 + 0x4176);
  memmove((void *)(iVar6 + 0x40c7),(void *)(iVar6 + 0x4177),(uint)*(byte *)(iVar6 + 0x4176));
  *(byte *)(iVar6 + 0x40d3) = *(byte *)(iVar6 + 0x4183);
  memmove((void *)(iVar6 + 0x40d4),(void *)(iVar6 + 0x4184),(uint)*(byte *)(iVar6 + 0x4183));
  memmove((void *)(param_1 + 0x795084),(void *)(iVar6 + 0x41e6),0x24);
  memmove((void *)(param_1 + 0x79507e),(void *)(iVar6 + 0x41e0),5);
  memmove((void *)(param_1 + 0x795114),(void *)(iVar6 + 0x420a),8);
  *(undefined4 *)(iVar7 + 0xec) = *(undefined4 *)(iVar6 + 0x413a);
  *(undefined2 *)(iVar7 + 0xf0) = *(undefined2 *)(iVar6 + 0x413e);
  *(undefined4 *)(iVar7 + 0x17c) = *(undefined4 *)(iVar6 + 0x2124d4);
  *(undefined4 *)(iVar7 + 0x2c4) = *(undefined4 *)(iVar6 + 0x2124cc);
  *(undefined4 *)(iVar7 + 0xae0) = *(undefined4 *)(iVar6 + 0x413a);
  *(undefined2 *)(iVar7 + 0xae4) = *(undefined2 *)(iVar6 + 0x413e);
  *(char *)(iVar7 + 0xb7c) = *(char *)(iVar6 + 0x40d3) + *(char *)(iVar6 + 0x40c6);
  uVar13 = (uint)*(byte *)(iVar6 + 0x4190);
  *(byte *)(iVar6 + 0x40fe) =
       *(byte *)(iVar6 + 0x40fe) & 0x9f | (*(byte *)(iVar6 + 0x41ab) & 3) << 5;
  *(byte *)(iVar6 + 0x40fc) =
       (byte)((uVar13 << 0x1c) >> 0x1e) | (byte)(((uVar13 << 0x1b) >> 0x1f) << 2) |
       (byte)(((uVar13 << 0x1a) >> 0x1f) << 3) | (byte)(((uVar13 << 0x19) >> 0x1f) << 4) |
       (*(byte *)(iVar6 + 0x4190) >> 7) << 5 | *(char *)(iVar6 + 0x4191) << 6;
  uVar13 = *(ushort *)(iVar6 + 0x40fe) & 0xfffffe7f | (*(byte *)(iVar6 + 0x41ac) & 3) << 7;
  *(short *)(iVar6 + 0x40fe) = (short)uVar13;
  *(byte *)(iVar6 + 0x40ff) =
       (byte)(uVar13 >> 8) & 0xfd | (byte)((((uint)*(byte *)(iVar6 + 0x41ac) << 0x1d) >> 0x1f) << 1)
  ;
  memmove((void *)(iVar7 + 0xca7),(void *)(iVar6 + 0x40e2),0x10);
  iVar4 = DebugLevel;
  *(uint *)(iVar6 + 0x212464) = *(uint *)(iVar6 + 0x212464) | 1;
  *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) & 0xfffffffd;
  *(uint *)(iVar6 + 0x212464) = *(uint *)(iVar6 + 0x212464) | 0x80;
  if (iVar4 < 1) {
LAB_00072198:
    *(undefined4 *)(iVar6 + 0x21245c) = jiffies;
  }
  else {
    pcVar10 = "ADHOC";
    if (param_2 != 0) {
      pcVar10 = "Infra";
    }
    printk("!!!%s LINK UP !!!\n",pcVar10);
    if (DebugLevel < 1) goto LAB_00072198;
    uVar8 = param_3[5];
    uVar2 = *(undefined1 *)((int)param_3 + 0xe);
    uVar12 = (uint)*(ushort *)(iVar6 + 0x40b0);
    uVar13 = (uint)*(byte *)((int)param_3 + 0x1a);
    uVar9 = wlan_operate_get_cen_ch_1(param_3);
    printk("!!! LINK UP !!! wdev(type=%d,func_idx=%d), (BssType=%d, AID=%d, ssid=%s, Channel=%d, CentralChannel = %d)\n"
           ,uVar8,uVar2,param_2,uVar12,__src,uVar13,uVar9);
    uVar8 = jiffies;
    *(undefined4 *)(iVar6 + 0x21245c) = jiffies;
    if (2 < DebugLevel) {
      printk("!!! LINK UP !!! (Density =%d, )\n",*(undefined1 *)(iVar7 + 0xd04),DebugLevel,uVar8,
             uVar12,__src,uVar13,uVar9);
    }
  }
  HW_SET_SLOTTIME(param_1,1,*(undefined1 *)((int)param_3 + 0x1a),param_3);
  if (*(char *)(iVar6 + 0x40e0) == '\x01') {
    uVar13 = param_3[0x237];
    param_3[0x237] = uVar13 & 0xffffffdf;
    uVar13 = uVar13 & 0xffffffdf | 1 << (*(byte *)(iVar6 + 0x41ac) & 3);
    param_3[0x237] = uVar13;
    if ((*(byte *)(iVar6 + 0x41ac) & 4) == 0) {
      param_3[0x237] = uVar13 & 0xffffff7f;
    }
    else {
      param_3[0x237] = uVar13 | 0x80;
    }
    HW_SET_PROTECT(param_1,param_3,0,0,0);
  }
  if ((*(int *)(param_1 + 0x795064) != 0) && ((*(ushort *)(iVar6 + 0x40b4) & 0x20) != 0)) {
    MlmeSetTxPreamble(param_1,1);
  }
  *(undefined1 *)(iVar11 + 4) = 0;
  LinkUp_Infra(param_1,param_3,iVar7,&local_48,(uint)bVar1,param_4,param_5);
  if (2 < DebugLevel) {
    printk("NDIS_STATUS_MEDIA_CONNECT Event B!.BACapability = %x. ClientStatusFlags = %lx\n",
           *(undefined4 *)(param_1 + 0x795044),*(undefined4 *)(iVar7 + 0xb4));
  }
  iVar11 = param_1 + 0x285958;
  *(undefined4 *)(param_1 + 0x829214) = 0;
  *(undefined4 *)(param_1 + 0x82921c) = 0;
  *(undefined1 *)(iVar6 + 0x212468) = 0;
  *(undefined4 *)(param_1 + 0xa39fa4) = 0;
  _raw_spin_lock_bh(iVar11);
  *(undefined2 *)(iVar7 + 0xbc) = *(undefined2 *)((int)param_3 + 0x8b2);
  if (*(char *)(param_3 + 0x22c) == '\0') {
    if ((*(byte *)(iVar7 + 0xbc) & 0x3f) == 0x20) {
      *(byte *)(iVar7 + 0xbd) = *(byte *)(iVar7 + 0xbd) & 0xfd;
LAB_00072528:
      *(byte *)(iVar7 + 0xbd) = *(byte *)(iVar7 + 0xbd) & 0xfb;
    }
    else if (7 < (*(byte *)(iVar7 + 0xbc) & 0x3f)) goto LAB_00072528;
    if (*(byte *)(iVar7 + 0xbd) < 0x40) {
      RTMPUpdateLegacyTxSetting(((uint)*(byte *)((int)param_3 + 0x8af) << 0x1a) >> 0x1d,iVar7);
    }
    OS_CLEAR_BIT(0,param_3 + 0x223);
    _raw_spin_unlock_bh(iVar11);
    iVar11 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar11 != 2) goto LAB_00072368;
    *(undefined1 *)(iVar7 + 0xb7e) = 0;
    if (0x7f < *(byte *)(iVar7 + 0xbd)) {
      bVar1 = *(byte *)((int)param_3 + 0x8ae);
      cVar5 = wlan_operate_get_tx_stream(param_3);
      *(byte *)(iVar7 + 0xbc) =
           *(byte *)(iVar7 + 0xbc) & 0xc0 | (bVar1 & 0x7f) + (cVar5 + -1) * '\x10' & 0x3f;
    }
  }
  else {
    OS_CLEAR_BIT(0,param_3 + 0x223);
    _raw_spin_unlock_bh(iVar11);
    iVar11 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar11 != 2) goto LAB_00072368;
    *(undefined1 *)(iVar7 + 0xb7e) = 1;
  }
  RAInit(param_1,iVar7);
  if (2 < DebugLevel) {
    printk("%s():Send HW_STA_BF_SOUNDING_ADJUST Cmd\n","LinkUp");
  }
  if (*(char *)(param_1 + 0x286285) == '\0') {
    HW_STA_BF_SOUNDING_ADJUST(param_1,1,param_3);
  }
LAB_00072368:
  *(uint *)(param_1 + 0xa39f9c) = (uint)*(ushort *)(iVar7 + 0xbc);
  uVar8 = HcGetBandByWdev(param_3);
  AsicSetTxStream(param_1,(byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4,0,1,uVar8);
  *(undefined1 *)(param_1 + 0x795062) = 0;
  *(undefined4 *)(iVar6 + 0x21244e) = *__src_00;
  *(undefined2 *)(iVar6 + 0x212452) = *(undefined2 *)(iVar6 + 0x21242c);
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xffffbfff;
  if (((param_3[0x4b9] != 0) && (*(char *)(param_3 + 0xf32) != '\0')) &&
     (RtmpusecDelay(100000), *(char *)(iVar6 + 0x4060) == '\x01')) {
    *(undefined1 *)(param_3 + 0x4bb) = 1;
    param_3[0x4bd] = 5;
    param_3[0x4bc] = 5;
    memmove((void *)((int)param_3 + 0x134a),__src_00,6);
    memmove((void *)((int)param_3 + 0x2f39),__src_00,6);
    WscSendEapolStart(param_1,(void *)((int)param_3 + 0x134a),2,param_3);
  }
  if ((*(uint *)(iVar6 + 0x212464) & 1) != 0) {
    if (((*(char *)(param_1 + 0x79564e) == '\x01') && (*(byte *)((int)param_3 + 0x1a) < 0xf)) &&
       ((*(char *)(iVar6 + 0x40e0) == '\x01' && ((*(byte *)(iVar6 + 0x41c0) & 1) != 0)))) {
      *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) | 0x40000;
      BuildEffectedChannelList(param_1,param_3);
      if (2 < DebugLevel) {
        printk("LinkUP AP supports 20/40 BSS COEX, Dot11BssWidthTriggerScanInt[%d]\n",
               *(undefined2 *)(param_1 + 0x7956a2));
      }
    }
    else if ((2 < DebugLevel) && (printk("not supports 20/40 BSS COEX !!!\n"), 2 < DebugLevel)) {
      uVar2 = *(undefined1 *)((int)param_3 + 0x1a);
      uVar3 = *(undefined1 *)(param_1 + 0x79564e);
      uVar8 = wlan_operate_get_cen_ch_1(param_3);
      printk("pAd->CommonCfg Info: bBssCoexEnable=%d, Channel=%d, CentralChannel=%d, PhyMode=%d\n",
             uVar3,uVar2,uVar8,*(undefined2 *)(param_3 + 6));
      if ((2 < DebugLevel) &&
         (printk("pStaCfg->StaActive.SupportedHtPhy.bHtEnable=%d\n",*(undefined1 *)(iVar6 + 0x40e0))
         , 2 < DebugLevel)) {
        printk("pStaCfg->MlmeAux.ExtCapInfo.BssCoexstSup=%d\n",*(byte *)(iVar6 + 0x41c0) & 1);
      }
    }
  }
  *(undefined2 *)(param_1 + 0x28594a) = 5;
  *(undefined1 *)(iVar6 + 0x934) = 1;
  if (param_3[5] != 0x100) {
    netif_carrier_on(*param_3);
  }
  return;
}

