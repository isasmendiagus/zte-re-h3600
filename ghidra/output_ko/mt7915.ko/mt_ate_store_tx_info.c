// module: mt7915.ko
// function: mt_ate_store_tx_info @ 0x288fdc
// size: 1072 bytes
//

int mt_ate_store_tx_info
              (int param_1,int param_2,undefined4 param_3,void *param_4,int param_5,byte *param_6)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char cVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  undefined4 uVar12;
  
  iVar2 = net_ad_wrap_service();
  if (*(int *)(iVar2 + param_2 * 0xd18 + 0x4e4) == 0) {
    if (DebugLevel < 0) {
      return -1;
    }
    printk("%s: Invalid pre-allocated buffer for MPDU\n","mt_ate_store_tx_info");
    return -1;
  }
  iVar2 = net_ad_wrap_service(param_1);
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    cVar7 = '\x10';
  }
  else {
    cVar7 = '\b';
  }
  if (*(char *)(iVar2 + param_2 * 0xd18 + 0x6f5) == cVar7) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Stack is full!\n","mt_ate_store_tx_info");
    return 0;
  }
  if (param_6 == (byte *)0x0) goto LAB_0028912c;
  if (param_5 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Insert mac_table_entry failed\n","mt_ate_store_tx_info");
    }
    goto LAB_0028912c;
  }
  __memzero(param_5 + 0xc4,0x1c);
  bVar1 = *param_6;
  *(byte *)(param_5 + 0xc4) = bVar1;
  *(byte *)(param_5 + 0xcb) = param_6[8];
  *(byte *)(param_5 + 0xcc) = param_6[9];
  *(byte *)(param_5 + 200) = param_6[2];
  *(byte *)(param_5 + 199) = param_6[3];
  *(byte *)(param_5 + 0xc6) = param_6[1];
  *(byte *)(param_5 + 0xcd) = param_6[7];
  *(byte *)(param_5 + 0xc9) = param_6[5];
  *(byte *)(param_5 + 0xca) = param_6[4];
  if (bVar1 < 5) {
    *(uint *)(param_5 + 0xd0) = param_6[6] & 0x1f;
    if (bVar1 == 0) {
      uVar8 = *(uint *)(param_1 + 0x795124) & 0xffffffef;
      *(uint *)(param_1 + 0x795124) = uVar8;
      if (*(uint *)(param_5 + 0xd0) < 9) {
        bVar1 = *(byte *)(param_5 + 0xc4);
      }
      else {
        *(uint *)(param_1 + 0x795124) = uVar8 | 0x10;
        bVar1 = *(byte *)(param_5 + 0xc4);
        *(int *)(param_5 + 0xd0) = *(int *)(param_5 + 0xd0) + -9;
      }
      if (4 < bVar1) goto LAB_00289118;
    }
    if ((param_6[6] & 0x7f) == 0x20) {
      mt_ate_mcs32_handle(param_1,*(undefined2 *)(param_5 + 0xe0),param_6[1]);
    }
  }
  else {
    *(uint *)(param_5 + 0xd0) = param_6[6] & 0xf;
    *(byte *)(param_5 + 0xd4) = (byte)(((uint)param_6[6] << 0x1a) >> 0x1f);
    if (bVar1 == 9) {
      *(byte *)(param_5 + 0xd5) = (byte)(((uint)param_6[6] << 0x1b) >> 0x1f);
    }
  }
LAB_00289118:
  wdev_do_conn_act(param_3,param_5);
LAB_0028912c:
  iVar2 = net_ad_wrap_service(param_1);
  iVar9 = param_2 * 0xd18;
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    uVar8 = 0x10;
  }
  else {
    uVar8 = 8;
  }
  iVar2 = iVar2 + iVar9;
  if (*(byte *)(iVar2 + 0x6f5) < uVar8) {
    os_move_mem((void *)(iVar2 + 0x6f4 + (uint)*(byte *)(iVar2 + 0x6f5) * 6 + 6),param_4,6);
    bVar1 = *(byte *)(iVar2 + 0x6f5);
    uVar10 = (uint)bVar1;
    iVar5 = iVar2 + 0x6f4 + uVar10 * 4;
    *(undefined4 *)(iVar5 + 0xa8) = param_3;
    *(int *)(iVar5 + 0x68) = param_5;
    *(byte *)(iVar2 + 0x6f5) = bVar1 + 1;
    pbVar3 = (byte *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    uVar8 = (uint)*pbVar3;
    iVar2 = net_ad_wrap_service(param_1);
    uVar12 = *(undefined4 *)(iVar2 + iVar9 + 0x4e4);
    iVar5 = net_ad_wrap_service(param_1);
    iVar2 = 0;
    if (param_6 != (byte *)0x0) {
      iVar2 = *(int *)(param_6 + 0xc);
    }
    iVar6 = *(int *)(iVar5 + iVar9 + 0x10f0);
    if (param_6 == (byte *)0x0) {
      iVar2 = net_ad_wrap_service(param_1);
      iVar2 = *(int *)(iVar2 + iVar9 + 0x6dc);
    }
    iVar4 = net_ad_wrap_service(param_1);
    MT_ATEComposePkt(param_1,uVar12,param_2,uVar10);
    iVar4 = param_2 * 0xd18 + iVar4 + 0x6f4;
    iVar11 = iVar4 + uVar10 * 4;
    if (iVar6 != 0) {
      iVar2 = *(int *)(iVar5 + iVar9 + 0x10f8);
    }
    if (*(int *)(iVar11 + 0xe8) != 0) {
      RTMPFreeNdisPacket(param_1);
      *(undefined4 *)(iVar11 + 0xe8) = 0;
    }
    if (3 < DebugLevel) {
      printk("%s: Alloc pkt, txlen=%d, tx_hw_hdr_len=%d, total=%d\n","mt_ate_store_tx_info",iVar2,
             uVar8,iVar2 + uVar8);
    }
    iVar2 = RTMPAllocateNdisPacket(param_1,iVar4 + (uVar10 + 0x3a) * 4,0,0,uVar12,iVar2 + uVar8);
    if (iVar2 != 0) {
      if (-1 < DebugLevel) {
        printk("%s: AllocateNdisPacket fail\n","mt_ate_store_tx_info");
        return iVar2;
      }
      return iVar2;
    }
  }
  else if ((-1 < DebugLevel) &&
          (printk("(%s)Stack for MAC_TABL_ENRTY is full!\n","mt_ate_push_mac_tbl_entry"),
          -1 < DebugLevel)) {
    printk("%s: mac_table_entry stored failed\n","mt_ate_store_tx_info");
    return 0;
  }
  return 0;
}

