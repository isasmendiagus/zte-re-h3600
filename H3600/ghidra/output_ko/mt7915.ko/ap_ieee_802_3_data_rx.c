// module: mt7915.ko
// function: ap_ieee_802_3_data_rx @ 0x1eea8
// size: 1024 bytes
//

undefined4 ap_ieee_802_3_data_rx(int param_1,int param_2,int param_3,uint *param_4)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  code *pcVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  byte *pbVar10;
  
  pbVar10 = *(byte **)(param_3 + 0x1c);
  pbVar8 = *(byte **)(param_3 + 0x10);
  iVar9 = *(int *)(param_2 + 0x904);
  if (param_4 != (uint *)0x0) {
    if (3 < DebugLevel) {
      uVar3 = *(uint *)(param_3 + 0x44);
      printk("%s(): wcid=%d, wdev_idx=%d, pRxBlk->Flags=0x%x, fRX_AP/STA/ADHOC=0x%x/0x%x/0x%x, Type/SubType=%d/%d, FrmDS/ToDS=%d/%d\n"
             ,"ap_ieee_802_3_data_rx",(short)param_4[0x38],*(undefined1 *)(param_2 + 0xc),uVar3,
             uVar3 & 0x100,uVar3 & 0x200,uVar3 & 0x400,((uint)*pbVar10 << 0x1c) >> 0x1e,
             *pbVar10 >> 4,((uint)pbVar10[1] << 0x1e) >> 0x1f,pbVar10[1] & 1);
    }
    pcVar6 = *(code **)(iVar9 + 0x68);
    if (pcVar6 != (code *)0x0) {
      (*pcVar6)(param_1,param_2,param_3);
    }
    param_4[0x2ba] = 0;
    *(undefined4 *)(param_1 + (uint)(ushort)param_4[0x38] * 0x620 + 0x2f954) = 0;
    uVar3 = param_4[0x4c6];
    uVar1 = *(ushort *)(param_3 + 0x48);
    param_4[0x4c6] = uVar3 + uVar1;
    param_4[0x4c7] = param_4[0x4c7] + (uint)CARRY4(uVar3,(uint)uVar1);
    param_4[0x4d7] = (uint)*(ushort *)(param_3 + 0x48) + param_4[0x4d7];
    *(uint *)(param_1 + 0xa78a1c) = (uint)*(ushort *)(param_3 + 0x48) + *(int *)(param_1 + 0xa78a1c)
    ;
    uVar3 = param_4[0x4c2];
    param_4[0x4c2] = uVar3 + 1;
    param_4[0x4c3] = param_4[0x4c3] + (uint)(0xfffffffe < uVar3);
    param_4[0x4e2] = param_4[0x4e2] + 1;
    if (**(char **)(param_3 + 0x1c) < '\0') {
      if ((*(short *)(param_1 + ((uint)*(ushort *)(param_3 + 0x4e) * 0xa60 +
                                 (uint)*(byte *)(param_3 + 0x53) + 0x514f8) * 2 + 4) == 0) ||
         ((*pbVar8 & 0x10) == 0)) {
        *pbVar8 = *pbVar8 & 0xfe;
      }
      else {
        *pbVar8 = *pbVar8 | 1;
      }
      if (*(char *)(param_3 + 0x73) != '\0') {
        *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 2;
      }
      if ((*pbVar8 & 1) != 0) {
        *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 1;
      }
    }
    iVar2 = rx_chk_duplicate_frame(param_1,param_3,param_2);
    if (iVar2 == 1) {
      if (2 < DebugLevel) {
        printk("%s(): duplicate frame drop it!\n","ap_ieee_802_3_data_rx");
      }
      wlan_dbg_set_last_error(0,1,0xff9,"ap_ieee_802_3_data_rx");
      return 0;
    }
    iVar2 = rx_chk_amsdu_invalid_frame(param_1,param_3,param_2);
    if (iVar2 != 1) {
      if ((*(char *)(param_3 + 0x22) == '\0') && ((pbVar10[1] & 4) != 0)) {
        de_fragment_data_pkt(param_1,param_3);
      }
      if ((*pbVar8 & 0x10) != 0) {
        param_4[0x4e] = (uint)*(ushort *)(param_3 + 0x62);
      }
      if (((*param_4 == 0x20001) || ((*param_4 & 4) != 0)) && (*(char *)(param_2 + 0x890) != '\0'))
      {
        bVar5 = **(byte **)(param_3 + 0x30);
        if (bVar5 == 0xff) {
          bVar5 = 0;
        }
        else {
          bVar5 = bVar5 & 1;
        }
        if (bVar5 != 0) {
          uVar1 = *(ushort *)(*(int *)(param_3 + 0x3c) + 0xc);
          uVar1 = uVar1 << 8 | uVar1 >> 8;
          if (uVar1 == 0x800) {
            IGMPSnooping(param_1,*(byte **)(param_3 + 0x30),*(undefined4 *)(param_3 + 0x2c),
                         *(int *)(param_3 + 0x3c) + 0xc,param_4,*(undefined2 *)(param_3 + 0x4e));
          }
          else if (uVar1 == 0x86dd) {
            MLDSnooping(param_1);
          }
        }
      }
      iVar7 = *(int *)(param_3 + 0x38);
      iVar2 = CheckPPPOEPacket(param_1,iVar7);
      if ((iVar2 != 0) && ((short)param_4[0x332] == 0)) {
        *(undefined2 *)(param_4 + 0x332) = 1;
        uVar3 = 0;
        do {
          uVar4 = uVar3 & 0xff;
          uVar3 = uVar3 + 1;
          ba_ori_session_tear_down(param_1,(short)param_4[0x38],uVar4,0);
        } while (uVar3 != 8);
        iVar7 = *(int *)(param_3 + 0x38);
      }
      if (iVar7 != 0) {
        *(undefined2 *)(iVar7 + 0x42) = *(undefined2 *)(param_3 + 0x4e);
        rx_802_3_data_frm_announce(param_1,param_4,param_3,param_4[2]);
      }
      (**(code **)(iVar9 + 0x84))(param_1,param_2,*(undefined1 *)(param_3 + 0x4a),0);
      return 1;
    }
    if (2 < DebugLevel) {
      printk("%s(): invalid amsdu frame drop it!\n","ap_ieee_802_3_data_rx");
    }
    wlan_dbg_set_last_error(0,1,0x1002,"ap_ieee_802_3_data_rx");
  }
  return 0;
}

