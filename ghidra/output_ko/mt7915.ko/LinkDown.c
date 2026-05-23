// module: mt7915.ko
// function: LinkDown @ 0x72bb4
// size: 1692 bytes
//

void LinkDown(int param_1,uint param_2,undefined4 *param_3,undefined4 param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  
  if (param_3 == (undefined4 *)0x0) {
    if (0 < DebugLevel) {
      printk("%s,wdev(null)(caller:%pS)\n","LinkDown");
    }
  }
  else if (0 < DebugLevel) {
    printk("%s,wdev(type=%d,func_idx=%d)(caller:%pS)\n","LinkDown",param_3[5],
           *(undefined1 *)((int)param_3 + 0xe));
  }
  iVar2 = GetStaCfgByWdev(param_1,param_3);
  if (param_3[5] == 0x100) {
    iVar3 = param_3[1];
    if (iVar3 == 0) {
      return;
    }
    if (*(int *)(iVar3 + 0x4144) == 0) {
      return;
    }
    uVar1 = *(ushort *)(*(int *)(iVar3 + 0x4144) + 0xe0);
    uVar7 = HcGetMaxStaNum(param_1);
    if (uVar7 <= uVar1) {
      return;
    }
    iVar3 = *(int *)(iVar3 + 0x4144);
  }
  else {
    iVar3 = GetAssociatedAPByWdev(param_1,param_3);
    if (iVar3 != (uint)*(ushort *)(iVar2 + 0x2132e0) * 0x14c0 + param_1 + 0xa1d20) {
      return;
    }
  }
  if (((iVar2 != 0 && iVar3 != 0) && ("hif_set_WPDMA"[param_1 + 0xc] != '\x01')) &&
     (puVar8 = *(undefined4 **)(iVar3 + 8), puVar8 == param_3)) {
    if (0 < DebugLevel) {
      printk("[%s] wdev(type=%d,func_idx=%d),pEntry=%p,wcid=%d,addr=%02x:%02x:%02x:%02x:%02x:%02x\n"
             ,"LinkDown",param_3[5],*(undefined1 *)((int)param_3 + 0xe),iVar3,
             *(undefined2 *)(iVar3 + 0xe0),*(undefined1 *)(iVar3 + 0xec),
             *(undefined1 *)(iVar3 + 0xed),*(undefined1 *)(iVar3 + 0xee),
             *(undefined1 *)(iVar3 + 0xef),*(undefined1 *)(iVar3 + 0xf0),
             *(undefined1 *)(iVar3 + 0xf1));
    }
    if (((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) &&
       ((*(int *)(param_1 + 0xa77bb4) != 1 ||
        ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)))) {
      if ((puVar8[5] == 2) &&
         ((*(char *)(iVar2 + 0x2124c0) != '\0' ||
          ((*(uint *)(param_1 + 0xa39f84) & 0x40000000) != 0)))) {
        RTMP_FORCE_WAKEUP(param_1,iVar2);
        *(undefined4 *)(iVar2 + 0x2124ac) = 0;
      }
      iVar5 = DebugLevel;
      *(undefined1 *)(iVar2 + 0x934) = 0;
      if (2 < iVar5) {
        printk("!!! LINK DOWN !!!\n");
      }
      *(undefined1 *)(iVar2 + 0xbb4) = 0;
      if (puVar8[5] != 0x100) {
        netif_carrier_off(*puVar8);
      }
      LinkDown_Infra(param_1,puVar8,param_2 & 2,param_4);
      if (((param_2 & 2) != 0) && ((puVar8[0xb] & 0x12cf8) != 0)) {
        RTMPWPARemoveAllKeys(param_1,puVar8);
      }
      if (*(char *)(param_1 + 0x286285) == '\0') {
        if (2 < DebugLevel) {
          printk("%s():Send HW_STA_BF_SOUNDING_ADJUST Cmd\n","LinkDown");
        }
        HW_STA_BF_SOUNDING_ADJUST(param_1,0,puVar8);
      }
      TRTableResetEntry(param_1,*(undefined2 *)(puVar8 + 0x268));
      if ((((puVar8[5] != 0x100) &&
           (MacTableDeleteEntry(param_1,*(undefined2 *)(iVar3 + 0xe0),iVar3 + 0xec),
           (*(uint *)(param_1 + 0x795124) & 2) == 0)) && (puVar8[5] == 2)) &&
         ((iVar5 = wdev_do_linkdown(puVar8), iVar5 != 1 && (0 < DebugLevel)))) {
        printk("%s(): link down fail!!\n","LinkDown");
      }
      HW_SET_SLOTTIME(param_1,1,*(undefined1 *)((int)puVar8 + 0x1a),puVar8);
      AsicDisableSync(param_1,0);
      *(undefined4 *)(param_1 + 0x829214) = 0;
      *(undefined4 *)(param_1 + 0x82921c) = 0;
      __memzero(iVar2 + 0x4190,0x1a);
      __memzero(iVar2 + 0x41aa,0x16);
      iVar5 = DebugLevel;
      *(uint *)(iVar2 + 0x2123ec) = *(uint *)(iVar2 + 0x2123ec) & 0xfffffffe;
      *(undefined1 *)(iVar2 + 0x41cb) = 0xff;
      if (2 < iVar5) {
        printk("LinkDownCleanMlmeAux.ExtCapInfo!\n");
      }
      __memzero(iVar2 + 0x41c0,0xb);
      if (*(char *)(iVar2 + 0x2127b9) != '\0') {
        *(undefined1 *)(iVar2 + 0x2127b9) = 1;
        __memzero(iVar2 + 0x2127ba,8);
      }
      *(undefined1 *)(puVar8 + 0x222) = 2;
      uVar7 = 0;
      _raw_spin_lock_bh(param_1 + 0x285958);
      *(undefined1 *)(param_1 + (uint)*(ushort *)(iVar3 + 0xe0) * 0x620 + 0x2f762) =
           *(undefined1 *)(puVar8 + 0x222);
      _raw_spin_unlock_bh(param_1 + 0x285958);
      *(undefined4 *)(iVar2 + 0x2127b4) = 0;
      RTMP_IndicateMediaState(param_1,0);
      *(undefined4 *)(param_1 + 0xa39fa4) = 1;
      *(undefined1 *)(iVar2 + 0x40e0) = 0;
      __memzero(iVar2 + 0x21280c,0x28);
      *(undefined2 *)(iVar2 + 0x212834) = 0;
      *(undefined2 *)(iVar2 + 0x212c36) = 0;
      *(undefined4 *)(iVar2 + 0x21280c) = 0x28;
      __memzero(iVar2 + 0x2131c8,0x24);
      *(undefined1 *)(param_1 + 0x794cd5) = *(undefined1 *)(param_1 + 0x794cd6);
      *(undefined1 *)(param_1 + 0x794cd4) = *(undefined1 *)(param_1 + 0x794cd6);
      uVar4 = HcGetBandByWdev(puVar8);
      iVar3 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar4);
      AsicSetTxStream(param_1,(byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4,0,0,uVar4);
      AsicSetPiggyBack(param_1,0);
      *(undefined4 *)(param_1 + 0x795044) = *(undefined4 *)(param_1 + 0x795048);
      puVar8[0x237] = 0;
      HW_SET_PROTECT(param_1,puVar8,0,0,0);
      *(undefined1 *)(param_1 + 0x7956b5) = 0;
      *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) & 0xfffbffff;
      TriEventInit(param_1);
      iVar5 = *(byte *)(iVar3 + 0x49c) - 1;
      if (0 < iVar5) {
        do {
          uVar6 = uVar7 + 1 & 0xff;
          *(undefined1 *)(iVar3 + uVar7 * 0x14 + 1) = 0;
          uVar7 = uVar6;
        } while ((int)uVar6 < iVar5);
      }
      *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xffffbfff;
      if (*(char *)(iVar2 + 0x4060) != '\0') {
        *(undefined1 *)(iVar2 + 0xbc9) = 0;
      }
      *(undefined1 *)(iVar2 + 0x2131cc) = 0x81;
      *(undefined1 *)(iVar2 + 0x2131cd) = 0x81;
      *(undefined1 *)(iVar2 + 0x2131ce) = 0x81;
      __memzero(iVar2 + 0x213211,0x20);
      __memzero(iVar2 + 0x213209,6);
      *(undefined1 *)(iVar2 + 0x213210) = 0;
      *(undefined1 *)(iVar2 + 0x21320f) = 0;
      *(undefined1 *)(iVar2 + 0x213231) = 1;
      *(undefined1 *)(iVar2 + 0x41de) = 0;
      __memzero(iVar2 + 0x41df);
      if (puVar8[5] == 2) {
        sta_link_down_complete(iVar2);
        return;
      }
    }
  }
  return;
}

