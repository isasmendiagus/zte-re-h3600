// module: mt7915.ko
// function: sta_ieee_802_3_data_rx @ 0x53534
// size: 552 bytes
//

undefined4 sta_ieee_802_3_data_rx(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  code *pcVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  
  pbVar4 = *(byte **)(param_3 + 0x10);
  pbVar5 = *(byte **)(param_3 + 0x1c);
  iVar6 = *(int *)(param_2 + 0x904);
  if (3 < DebugLevel) {
    uVar3 = *(uint *)(param_3 + 0x44);
    printk("%s(): wcid=%d, wdev_idx=%d, pRxBlk->Flags=0x%x, fRX_AP/STA/ADHOC=0x%x/0x%x/0x%x, Type/SubType=%d/%d, FrmDS/ToDS=%d/%d\n"
           ,"sta_ieee_802_3_data_rx",*(undefined2 *)(param_4 + 0xe0),*(undefined1 *)(param_2 + 0xc),
           uVar3,uVar3 & 0x100,uVar3 & 0x200,uVar3 & 0x400,((uint)*pbVar5 << 0x1c) >> 0x1e,
           *pbVar5 >> 4,((uint)pbVar5[1] << 0x1e) >> 0x1f,pbVar5[1] & 1);
  }
  pcVar2 = *(code **)(iVar6 + 0x68);
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)(param_1,param_2,param_3);
  }
  *(undefined4 *)(param_4 + 0xae8) = 0;
  *(undefined4 *)(param_1 + (uint)*(ushort *)(param_4 + 0xe0) * 0x620 + 0x2f954) = 0;
  *(uint *)(param_1 + 0xa78a1c) = (uint)*(ushort *)(param_3 + 0x48) + *(int *)(param_1 + 0xa78a1c);
  if (**(char **)(param_3 + 0x1c) < '\0') {
    if ((*(short *)(param_1 + ((uint)*(ushort *)(param_3 + 0x4e) * 0xa60 +
                               (uint)*(byte *)(param_3 + 0x53) + 0x514f8) * 2 + 4) == 0) ||
       ((*pbVar4 & 0x10) == 0)) {
      *pbVar4 = *pbVar4 & 0xfe;
    }
    else {
      *pbVar4 = *pbVar4 | 1;
    }
    if (*(char *)(param_3 + 0x73) != '\0') {
      *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 2;
    }
    if ((*pbVar4 & 1) != 0) {
      *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 1;
    }
  }
  iVar6 = rx_chk_duplicate_frame(param_1,param_3,param_2);
  if (iVar6 == 1) {
    if (DebugLevel < 3) {
      uVar1 = 0;
    }
    else {
      printk("%s(): duplicate frame drop it!\n","sta_ieee_802_3_data_rx");
      uVar1 = 0;
    }
  }
  else {
    if ((*(char *)(param_3 + 0x22) == '\0') && ((pbVar5[1] & 4) != 0)) {
      de_fragment_data_pkt(param_1,param_3);
    }
    if ((*pbVar4 & 0x10) != 0) {
      *(uint *)(param_4 + 0x138) = (uint)*(ushort *)(param_3 + 0x62);
    }
    if (*(int *)(param_3 + 0x38) == 0) {
      uVar1 = 1;
    }
    else {
      rx_802_3_data_frm_announce(param_1,param_4,param_3,*(undefined4 *)(param_4 + 8));
      uVar1 = 1;
    }
  }
  return uVar1;
}

