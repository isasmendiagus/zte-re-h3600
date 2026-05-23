// module: mt7915.ko
// function: mt_op_set_test_mode_dnlk_2g @ 0x259424
// size: 440 bytes
//

undefined4 mt_op_set_test_mode_dnlk_2g(int param_1)

{
  char *pcVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  bool bVar8;
  uint local_3c;
  undefined1 local_38 [3];
  undefined1 uStack_35;
  uint local_34;
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
    pcVar1 = "SetPartProfileParameters" + iVar5 + 8;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    sys_ad_zero_mem(&local_3c,0x14);
    bVar8 = MT7915_DNL_CAL_GBAND_BW20_CH_SIZE != 0;
    *(uint *)(iVar5 + 0xa3ac14) = *(uint *)(iVar5 + 0xa3ac14) | 0x200;
    if (bVar8) {
      cVar4 = '\0';
      cVar3 = '\0';
      do {
        uStack_2c._0_3_ = CONCAT12(1,(undefined2)uStack_2c);
        bVar8 = *(char *)(iVar5 + 0x79504d) == '\0';
        if (bVar8) {
          _local_38 = CONCAT31(stack0xffffffc9,0xf);
        }
        bVar2 = *(byte *)((int)&MT7915_DNL_CAL_GBAND_BW20_CH + uVar7 * 2);
        if (bVar8) {
          local_38._0_2_ = CONCAT11(0xf,local_38[0]);
          uVar6 = _local_38;
        }
        else {
          cVar3 = "SetPartProfileParameters"[iVar5 + 0x1a];
          _local_38 = CONCAT22(stack0xffffffca,0x303);
          "SetPartProfileParameters"[iVar5 + 0x1a] = '\x03';
          cVar4 = "SetPartProfileParameters"[iVar5 + 0x1b];
          "SetPartProfileParameters"[iVar5 + 0x1b] = '\x03';
          uVar6 = _local_38;
        }
        local_3c._0_2_ = (ushort)bVar2;
        local_3c = (uint)CONCAT12(bVar2,(ushort)local_3c);
        uStack_35 = (undefined1)((uint)uVar6 >> 0x18);
        local_38._0_2_ = (undefined2)uVar6;
        local_38 = (undefined1  [3])CONCAT12(0,local_38._0_2_);
        local_34 = local_34 & 0xffffff00;
        MtCmdChannelSwitch(iVar5,local_3c,_local_38,local_34,local_30,uStack_2c);
        if (*(char *)(iVar5 + 0x79504d) == '\0') {
          local_38._0_2_ = 0xf0f;
        }
        else {
          local_38._0_2_ = 0x302;
          "SetPartProfileParameters"[iVar5 + 0x1a] = cVar3;
          "SetPartProfileParameters"[iVar5 + 0x1b] = cVar4;
        }
        MtCmdSetTxRxPath(iVar5,local_3c,_local_38,local_34,local_30,uStack_2c);
        uVar7 = uVar7 + 1 & 0xff;
      } while (uVar7 < MT7915_DNL_CAL_GBAND_BW20_CH_SIZE);
    }
    MtCmdDoCalibration(iVar5,1,0x8000000,0);
    MtCmdDoCalibration(iVar5,1,0x2000000,0);
    uVar6 = 0;
    *(uint *)(iVar5 + 0xa3ac14) = *(uint *)(iVar5 + 0xa3ac14) & 0xfffffdff;
  }
  return uVar6;
}

