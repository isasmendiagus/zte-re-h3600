// module: mt7915.ko
// function: dev_rx_mgmt_frm @ 0xcaa5c
// size: 508 bytes
//

void dev_rx_mgmt_frm(int param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  char cVar7;
  int iVar8;
  byte *pbVar9;
  
  pbVar9 = *(byte **)(param_2 + 0x1c);
  iVar8 = *(int *)(param_2 + 0x38);
  if (5 < DebugLevel) {
    printk("-->%s()\n","dev_rx_mgmt_frm");
  }
  if (*(ushort *)(param_2 + 0x40) < 0x901) {
    iVar3 = PMF_PerformRxFrameAction(param_1,param_2);
    if (iVar3 != 0) {
      uVar2 = *(ushort *)(param_2 + 0x4e);
      uVar4 = HcGetMaxStaNum(param_1);
      if (uVar2 < uVar4) {
        iVar3 = (uint)*(ushort *)(param_2 + 0x4e) * 0x14c0 + param_1 + 0xa1d20;
      }
      else {
        iVar3 = FUN_000c4f74(param_1,param_2);
      }
      cVar7 = *(char *)(param_1 + 0x286285);
      if (cVar7 == '\x01') {
        iVar5 = ap_dev_rx_mgmt_frm(param_1,param_2,iVar3);
        if (iVar5 != 0) {
          if ((((iVar3 == 0) || (puVar6 = *(undefined4 **)(iVar3 + 8), puVar6 == (undefined4 *)0x0))
              || (bVar1 = *pbVar9,
                 (bVar1 & 0xe0) != 0xa0 && ((bVar1 & 0xf0) != 0 && (bVar1 & 0xf0) != 0xc0))) ||
             ((puVar6[0x264] == 3 || (puVar6[5] == 2)))) {
            cVar7 = *(char *)(param_1 + 0x286285);
            goto LAB_000cab14;
          }
          if (DebugLevel < 0) goto LAB_000cab38;
          printk("ERROR: BSS idx (%d) wdev %s state %d not ready. (subtype %d)\n",
                 *(undefined1 *)((int)puVar6 + 0x999),*puVar6,puVar6[0x264],bVar1 >> 4);
        }
      }
      else {
LAB_000cab14:
        if (cVar7 == '\0') {
          sta_dev_rx_mgmt_frm(param_1,param_2,iVar3);
        }
      }
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("DataSize=%d\n");
    }
    if (*(int *)(param_2 + 0x1c) != 0) {
      hex_dump("MGMT ???",*(int *)(param_2 + 0x1c),2);
    }
  }
  if (5 < DebugLevel) {
    printk("<--%s()\n","dev_rx_mgmt_frm");
  }
LAB_000cab38:
  if (iVar8 == 0) {
    return;
  }
  RTMPFreeNdisPacket(param_1,iVar8);
  return;
}

