// module: mt7915.ko
// function: mt_op_set_test_mode_dnlk_5g @ 0x2595dc
// size: 464 bytes
//

undefined4 mt_op_set_test_mode_dnlk_5g(int param_1)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  bool bVar8;
  uint3 local_3c;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  iVar5 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar5 == 0) {
    uVar6 = 0x503;
  }
  else {
    uVar7 = 0;
    pcVar1 = "SetPartProfileParameters" + iVar5;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    pcVar1 = "SetPartProfileParameters" + iVar5 + 0x10;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    sys_ad_zero_mem(&local_3c,0x14);
    bVar8 = MT7915_DNL_CAL_ABAND_BW20_CH_SIZE != 0;
    *(uint *)(iVar5 + 0xa3ac14) = *(uint *)(iVar5 + 0xa3ac14) | 0x200;
    if (bVar8) {
      cVar3 = '\0';
      cVar2 = '\0';
      do {
        bVar8 = *(char *)(iVar5 + 0x79504d) == '\0';
        uVar4 = local_38 >> 0x10;
        local_34 = CONCAT22(local_34._2_2_,0x100);
        uStack_2c._0_3_ = CONCAT12(1,(undefined2)uStack_2c);
        local_3c = (uint3)(byte)MT7915_DNL_CAL_ABAND_BW20_CH[uVar7 * 2] << 0x10;
        _local_3c = CONCAT31(local_3c >> 8,MT7915_DNL_CAL_ABAND_BW20_CH[uVar7 * 2]);
        if (bVar8) {
          local_38._0_2_ = 0xf0f;
        }
        else {
          cVar2 = "rtmp_read_vow_parms_from_file"[iVar5];
          local_38._0_2_ = 0xc0c;
          cVar3 = "rtmp_read_vow_parms_from_file"[iVar5 + 1];
          "rtmp_read_vow_parms_from_file"[iVar5] = '\f';
          "rtmp_read_vow_parms_from_file"[iVar5 + 1] = '\f';
        }
        local_38 = CONCAT22((short)uVar4,(undefined2)local_38) & 0xff00ffff;
        local_34 = CONCAT31(local_34._1_3_,!bVar8);
        MtCmdChannelSwitch(iVar5,_local_3c,local_38,local_34,local_30,uStack_2c);
        if (*(char *)(iVar5 + 0x79504d) == '\0') {
          local_38._0_2_ = 0xf0f;
        }
        else {
          local_38._0_2_ = 0xc02;
          "rtmp_read_vow_parms_from_file"[iVar5] = cVar2;
          "rtmp_read_vow_parms_from_file"[iVar5 + 1] = cVar3;
        }
        MtCmdSetTxRxPath(iVar5,_local_3c,local_38,local_34,local_30,uStack_2c);
        uVar7 = uVar7 + 1 & 0xff;
      } while (uVar7 < MT7915_DNL_CAL_ABAND_BW20_CH_SIZE);
    }
    MtCmdDoCalibration(iVar5,1,0x8000000,0);
    MtCmdDoCalibration(iVar5,1,0x4000000,0);
    uVar6 = 0;
    *(uint *)(iVar5 + 0xa3ac14) = *(uint *)(iVar5 + 0xa3ac14) & 0xfffffdff;
  }
  return uVar6;
}

