// module: mt7915.ko
// function: send_data_pkt @ 0xc67d0
// size: 1260 bytes
//

undefined4 send_data_pkt(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  undefined4 *puVar8;
  int iVar9;
  int local_38;
  uint local_34;
  undefined1 auStack_30 [16];
  
  puVar8 = *(undefined4 **)(param_2 + 0x904);
  uVar3 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar5 = param_3;
  if ((uVar3 & 0x400) == 0) goto LAB_000c68a8;
  RTMP_QueryPacketInfo(param_3,auStack_30,&local_38,&local_34);
  if ((local_38 == 0) || (local_34 < 0xf)) goto LAB_000c69dc;
  if (((*(byte *)(param_3 + 0x72) & 1) != 0) &&
     (iVar9 = check_copy_pkt_needed(param_1,param_2,param_3), iVar9 != 0)) {
    iVar5 = RtmpVlanPktCopy(param_1,param_2,param_3);
    if (iVar5 == 0) {
      iVar5 = param_3;
      if (0 < DebugLevel) {
        printk("%s():copy packet fail!!\n","ap_fp_tx_pkt_vlan_tag_handle");
      }
      goto LAB_000c69dc;
    }
    RTMP_QueryPacketInfo(iVar5,auStack_30,&local_38,&local_34);
    if ((local_38 == 0) || (local_34 < 0xf)) goto LAB_000c69dc;
  }
  iVar9 = *(int *)(iVar5 + 0xcc);
  if (iVar9 == 0) {
    printk(&_LC10,0x141);
    dump_stack();
  }
  uVar1 = *(undefined1 *)(iVar9 + 0xc);
  if (CONCAT11(uVar1,*(undefined1 *)(iVar9 + 0xd)) == -0x7f00) {
    iVar6 = iVar5;
    if (iVar9 == 0) goto LAB_000c69dc;
  }
  else {
    *(undefined1 *)(iVar5 + 0x34) = *(undefined1 *)(iVar9 + 0xd);
    *(undefined1 *)(iVar5 + 0x35) = uVar1;
    *(byte *)(iVar5 + 0x30) = *(byte *)(iVar5 + 0x30) & 0xef;
    if (((*(char *)(param_2 + 0x8f8) == '\0') || (*(short *)(param_2 + 0x8fe) == 4)) ||
       (*(ushort *)(param_2 + 0x8fa) == 0)) {
      if (iVar9 != 0) goto LAB_000c68a8;
      goto LAB_000c69dc;
    }
    iVar6 = RtmpOsVLANInsertTag(iVar5,*(ushort *)(param_2 + 0x8fa) |
                                      *(short *)(param_2 + 0x8fc) << 0xd);
    if (iVar6 != 0) {
      iVar9 = *(int *)(iVar6 + 0xcc);
    }
    if (iVar9 == 0) {
      printk(&_LC10,0x155);
      dump_stack();
      goto LAB_000c69dc;
    }
  }
  if (*(ushort *)(param_2 + 0x8fa) == 0) goto LAB_000c6a7c;
  uVar7 = *(ushort *)(iVar9 + 0xe);
  if (*(ushort *)(param_2 + 0x8fa) == (ushort)((uVar7 & 0xf) << 8 | uVar7 >> 8)) {
    *(ushort *)(iVar9 + 0xe) = uVar7 & 0xff1f;
    *(ushort *)(iVar9 + 0xe) = uVar7 & 0xff1f | (*(ushort *)(param_2 + 0x8fc) & 7) << 5;
    goto LAB_000c6a7c;
  }
  switch(*(undefined2 *)(param_2 + 0x8fe)) {
  case 0:
  case 4:
    if (0 < DebugLevel) {
      printk("%s():Allow the packet\n","ap_fp_tx_pkt_vlan_tag_handle");
    }
    break;
  case 1:
    if (0 < DebugLevel) {
      printk("%s():Drop the packet\n","ap_fp_tx_pkt_vlan_tag_handle");
    }
    goto LAB_000c69dc;
  case 2:
    if (0 < DebugLevel) {
      printk("%s():Replace the packet VLAN ID\n","ap_fp_tx_pkt_vlan_tag_handle");
      uVar7 = *(ushort *)(iVar9 + 0xe);
    }
    *(ushort *)(iVar9 + 0xe) = uVar7 & 0xf0;
    *(ushort *)(iVar9 + 0xe) =
         uVar7 & 0xf0 | *(ushort *)(param_2 + 0x8fa) << 8 | *(ushort *)(param_2 + 0x8fa) >> 8;
    break;
  case 3:
    if (0 < DebugLevel) {
      printk("%s():Replace the packet VLAN Tag\n","ap_fp_tx_pkt_vlan_tag_handle");
      uVar7 = *(ushort *)(iVar9 + 0xe);
    }
    *(ushort *)(iVar9 + 0xe) = uVar7 & 0xff1f;
    uVar7 = uVar7 & 0x10 | (*(ushort *)(param_2 + 0x8fc) & 7) << 5;
    *(ushort *)(iVar9 + 0xe) = uVar7;
    *(ushort *)(iVar9 + 0xe) =
         uVar7 | *(ushort *)(param_2 + 0x8fa) << 8 | *(ushort *)(param_2 + 0x8fa) >> 8;
    break;
  default:
    if (-1 < DebugLevel) {
      printk("%s(): Unexpected checking policy\n","ap_fp_tx_pkt_vlan_tag_handle");
    }
    goto LAB_000c69dc;
  }
LAB_000c6a7c:
  if (iVar6 != 0) {
    if (*(char *)(param_2 + 0x8f8) == '\0') {
      remove_vlan_tag(param_1,iVar6);
      iVar9 = *(int *)(iVar6 + 0xcc);
      *(byte *)(iVar6 + 0x30) = *(byte *)(iVar6 + 0x30) & 0xef;
      if (iVar9 == 0) {
        printk(&_LC10,0x1a2);
        dump_stack();
      }
      uVar1 = *(undefined1 *)(iVar9 + 0xc);
      *(undefined1 *)(iVar6 + 0x34) = *(undefined1 *)(iVar9 + 0xd);
      *(undefined1 *)(iVar6 + 0x35) = uVar1;
    }
    else {
      *(byte *)(iVar6 + 0x45) = (byte)*(undefined2 *)(iVar9 + 0xe) >> 5;
      *(byte *)(iVar6 + 0x30) = *(byte *)(iVar6 + 0x30) | 0x10;
      uVar3 = (uint)*(byte *)(iVar9 + 0x11) + (uint)*(byte *)(iVar9 + 0x10) * 0x100 & 0xffff;
      *(char *)(iVar6 + 0x34) = (char)uVar3;
      *(char *)(iVar6 + 0x35) = (char)(uVar3 >> 8);
    }
LAB_000c68a8:
    uVar3 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if ((uVar3 & 0x400) == 0) {
      cVar2 = (*(code *)puVar8[3])(param_1,param_2,iVar5);
      if (cVar2 != '\0') {
        uVar4 = (*(code *)*puVar8)(param_1,param_2,iVar5);
        return uVar4;
      }
      uVar4 = 0x55d;
    }
    else {
      cVar2 = (*(code *)puVar8[4])(param_1,param_2,iVar5);
      if (cVar2 != '\0') {
        uVar4 = (*(code *)puVar8[1])(param_1,param_2,iVar5);
        return uVar4;
      }
      uVar4 = 0x553;
    }
    *(int *)(param_1 + 0x9db7c) = *(int *)(param_1 + 0x9db7c) + 1;
    wlan_dbg_set_last_error(0,0,uVar4,"send_data_pkt");
    RTMPFreeNdisPacket(param_1,iVar5);
    return 0;
  }
LAB_000c69dc:
  RTMPFreeNdisPacket(param_1,iVar5);
  return 1;
}

