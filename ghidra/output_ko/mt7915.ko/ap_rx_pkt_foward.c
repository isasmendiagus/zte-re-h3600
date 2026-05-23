// module: mt7915.ko
// function: ap_rx_pkt_foward @ 0x1d7b8
// size: 932 bytes
//

byte ap_rx_pkt_foward(int param_1,undefined4 *param_2,int param_3)

{
  undefined1 uVar1;
  byte bVar2;
  uint uVar3;
  int *piVar4;
  byte bVar5;
  int iVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  ushort local_2a [3];
  
  bVar5 = *(byte *)((int)param_2 + 0xe);
  uVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar3 <= bVar5) || (uVar3 = (uint)*(byte *)((int)param_2 + 0xe), 0x1f < uVar3)) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s():Invalid func_idx(%d), type(%d)!\n","ap_rx_pkt_foward",
           *(undefined1 *)((int)param_2 + 0xe),param_2[5]);
    return 0;
  }
  if (*(ushort *)(param_1 + 0x285920) < 2) {
    return 1;
  }
  pbVar7 = *(byte **)(param_3 + 0xcc);
  bVar5 = *pbVar7;
  bVar2 = bVar5 & 1;
  if ((bVar5 & 1) != 0) {
    iVar6 = uVar3 * 0x5834 + param_1;
    if ((byte)"pStaCfg->WpaPassPhrase"[iVar6 + 0xb] < 2) {
      return 1;
    }
    if ("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n"[iVar6 + 0x30] != '\0') {
      return 1;
    }
    if (bVar5 != 0xff && CONCAT11(pbVar7[0xc],pbVar7[0xd]) == -0x76c6) {
      return 1;
    }
    iVar6 = DuplicatePacket(*param_2,param_3);
    bVar5 = 1;
    if (iVar6 == 0) {
      return 1;
    }
    local_2a[0] = *(ushort *)(param_2 + 4);
    uVar1 = *(undefined1 *)(param_2 + 3);
    *(ushort *)(iVar6 + 0x42) = local_2a[0];
    *(undefined1 *)(iVar6 + 0x2d) = uVar1;
    goto LAB_0001d998;
  }
  piVar4 = (int *)MacTableLookup(param_1,pbVar7);
  if (piVar4 == (int *)0x0) {
LAB_0001d8fc:
    iVar6 = a4_proxy_lookup(param_1,*(undefined1 *)((int)param_2 + 0xe),pbVar7,0,1,local_2a);
    if (iVar6 == 0) {
      return 1;
    }
    uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (local_2a[0] < uVar3) {
      piVar4 = (int *)((uint)local_2a[0] * 0x14c0 + param_1 + 0xa1d20);
    }
    if (piVar4 == (int *)0x0) {
      return 1;
    }
    if (*piVar4 != 0x20001) {
      return 1;
    }
    puVar8 = (undefined4 *)piVar4[2];
    iVar6 = DuplicatePacket(*param_2,param_3);
  }
  else {
    if ((piVar4[0x3f] != 2) || (puVar9 = (undefined4 *)piVar4[2], puVar9 == (undefined4 *)0x0)) {
      if (*piVar4 != 0x10) {
        return 1;
      }
      goto LAB_0001d8fc;
    }
    if (param_2 != puVar9) {
      bVar2 = 0;
      if (*(int *)(&DAT_003678f4 + param_1) != 1) {
        bVar2 = 1;
      }
LAB_0001da20:
      iVar6 = MacTableLookup(param_1,pbVar7 + 6);
      if (iVar6 == 0) {
        return bVar2;
      }
      if (0x11f < *(ushort *)(iVar6 + 0xe2)) {
        return bVar2;
      }
      if (*(char *)(param_1 + (uint)*(ushort *)(iVar6 + 0xe2) * 0x620 + 0x2f762) == '\x01') {
        return bVar2;
      }
LAB_0001da5c:
      if (DebugLevel < 3) {
        return 0;
      }
      printk("%s(): Not PortSecured Pkt FWD to STAs from wcid(%d)to wcid(%d)!\n","ap_rx_pkt_foward",
             *(undefined2 *)(iVar6 + 0xe0),(short)piVar4[0x38]);
      return 0;
    }
    if (*(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" +
                uVar3 * 0x5834 + param_1 + 0x2c) == 1) goto LAB_0001da20;
    iVar6 = MacTableLookup(param_1,pbVar7 + 6);
    puVar8 = param_2;
    if (iVar6 == 0) {
LAB_0001daf4:
      iVar6 = DuplicatePacket(*param_2,param_3);
    }
    else {
      if (*(ushort *)(iVar6 + 0xe2) < 0x120) {
        puVar8 = puVar9;
        if (*(char *)((uint)*(ushort *)(iVar6 + 0xe2) * 0x620 + param_1 + 0x2f762) != '\x01')
        goto LAB_0001da5c;
        goto LAB_0001daf4;
      }
      iVar6 = DuplicatePacket(*param_2,param_3);
    }
  }
  if (iVar6 == 0) {
    return 0;
  }
  bVar5 = 0;
  local_2a[0] = *(ushort *)(piVar4 + 0x38);
  *(undefined1 *)(iVar6 + 0x2d) = *(undefined1 *)(puVar8 + 3);
  *(ushort *)(iVar6 + 0x42) = local_2a[0];
LAB_0001d998:
  *(undefined1 *)(iVar6 + 0x2c) = 1;
  *(undefined1 *)(iVar6 + 0x2f) = 0;
  iVar6 = send_data_pkt(param_1,param_2,iVar6);
  if (iVar6 == 0) {
    bVar2 = *pbVar7 & 1;
  }
  else {
    bVar2 = 0;
  }
  if (bVar2 != 0) {
    a4_send_clone_pkt(param_1,*(undefined1 *)((int)param_2 + 0xe),param_3,pbVar7 + 6);
  }
  return bVar5;
}

