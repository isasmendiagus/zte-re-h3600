// module: mt7915.ko
// function: mt_ate_enq_pkt @ 0x286eb0
// size: 556 bytes
//

undefined4 mt_ate_enq_pkt(undefined4 param_1,int param_2,uint param_3)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 uVar6;
  int iVar7;
  char cVar8;
  int iVar9;
  bool bVar10;
  bool bVar11;
  
  iVar3 = net_ad_wrap_service();
  iVar7 = param_2 * 0xd18;
  iVar4 = net_ad_wrap_service(param_1);
  iVar9 = *(int *)(iVar3 + iVar7 + 0x10f0);
  cVar8 = *(char *)(iVar3 + iVar7 + 0x1106);
  uVar1 = *(ushort *)(iVar4 + iVar7 + 0x50e);
  iVar3 = net_ad_wrap_service(param_1);
  if (param_3 < *(byte *)(iVar3 + iVar7 + 0x6f5)) {
    iVar4 = iVar3 + iVar7 + 0x6f4 + param_3 * 4;
    iVar3 = *(int *)(iVar4 + 0x68);
    if (3 < DebugLevel) {
      printk("%s: band_idx:%u, ring Idx:%u\n","mt_ate_enq_pkt",param_2,uVar1);
    }
    if (iVar3 == 0) {
      if (-1 < DebugLevel) {
        printk("%s: mac_tbl_entry for index[%d] is invalid, ignored\n","mt_ate_enq_pkt",param_3);
        return 0xffffffff;
      }
    }
    else {
      iVar7 = *(int *)(iVar4 + 0xe8);
      if (iVar7 != 0) {
        iVar4 = *(int *)(iVar4 + 0xa8);
        if (iVar4 == 0) {
          iVar4 = net_ad_wrap_service(param_1);
          iVar4 = *(int *)(param_2 * 0xd18 + iVar4 + 0x504);
        }
        iVar7 = skb_clone(iVar7,0x20);
        g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
        if (iVar7 == 0) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: clone pakcet fail, ignored\n","mt_ate_enq_pkt");
          return 0;
        }
        bVar10 = cVar8 != '\0';
        bVar11 = iVar9 != 0;
        uVar6 = 8;
        if (!bVar10 || !bVar11) {
          cVar8 = '\0';
        }
        *(undefined1 *)(iVar7 + 0x2d) = *(undefined1 *)(iVar4 + 0xc);
        if (bVar10 && bVar11) {
          cVar8 = '\x01';
        }
        uVar2 = *(undefined2 *)(iVar3 + 0xe0);
        *(undefined1 *)(iVar7 + 0x36) = 8;
        if (bVar10 && bVar11) {
          uVar6 = 0;
        }
        else {
          *(char *)(iVar7 + 0x4d) = cVar8;
        }
        *(undefined2 *)(iVar7 + 0x42) = uVar2;
        if (bVar10 && bVar11) {
          *(undefined1 *)(iVar7 + 0x4f) = uVar6;
          *(undefined1 *)(iVar7 + 0x4d) = 1;
        }
        else {
          *(undefined1 *)(iVar7 + 0x4f) = 2;
        }
        uVar5 = send_mlme_pkt(param_1,iVar7,iVar4,uVar1 & 0xff,1);
        return uVar5;
      }
      if (-1 < DebugLevel) {
        printk("%s: packet for index[%d] is invalid, ignored\n","mt_ate_enq_pkt",param_3);
        return 0xffffffff;
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: invalid sta_idx=%d and stack depth:%d, ignored\n","mt_ate_enq_pkt",param_3);
  }
  return 0xffffffff;
}

