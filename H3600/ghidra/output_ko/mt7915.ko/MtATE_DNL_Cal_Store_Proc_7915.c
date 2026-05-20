// module: mt7915.ko
// function: MtATE_DNL_Cal_Store_Proc_7915 @ 0x27ea64
// size: 956 bytes
//

undefined4 MtATE_DNL_Cal_Store_Proc_7915(int param_1,undefined4 param_2)

{
  char *pcVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  bool bVar6;
  uint local_3c;
  undefined1 local_38;
  undefined1 local_37 [3];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  iVar3 = simple_strtol(param_2,0,10);
  if (("cp_support_is_enabled"[param_1 + 4] - 2U & 0xfd) != 0) {
    if (-1 < DebugLevel) {
      printk("%s: Currently not in FLASH or BIN MODE,return.\n","MtATE_DNL_Cal_Store_Proc_7915");
    }
    return 0;
  }
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    if (2 < DebugLevel) {
      printk("Single Band\n");
    }
  }
  else if (2 < DebugLevel) {
    printk("Dual Band\n");
  }
  if (iVar3 == 0) {
    uVar4 = *(undefined4 *)("SetPartProfileParameters" + param_1 + 4);
    pcVar1 = "SetPartProfileParameters" + param_1;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    os_zero_mem(uVar4,0x278);
    uVar4 = *(undefined4 *)("SetPartProfileParameters" + param_1 + 0xc);
    pcVar1 = "SetPartProfileParameters" + param_1 + 8;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    os_zero_mem(uVar4,0x24);
    uVar4 = *(undefined4 *)("SetPartProfileParameters" + param_1 + 0x14);
    pcVar1 = "SetPartProfileParameters" + param_1 + 0x10;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    os_zero_mem(uVar4,0xc0);
    return 1;
  }
  if (iVar3 == 1) {
    uVar5 = 0;
    pcVar1 = "SetPartProfileParameters" + param_1;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    pcVar1 = "SetPartProfileParameters" + param_1 + 8;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    os_zero_mem(&local_3c,0x14);
    bVar6 = MT7915_DNL_CAL_GBAND_BW20_CH_SIZE != 0;
    *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) | 0x200;
    if (bVar6) {
      do {
        bVar2 = *(byte *)((int)&MT7915_DNL_CAL_GBAND_BW20_CH + uVar5 * 2);
        bVar6 = *(char *)(param_1 + 0x79504d) == '\0';
        if (bVar6) {
          _local_38 = CONCAT31(local_37,4);
        }
        uVar5 = uVar5 + 1 & 0xff;
        if (bVar6) {
          _local_38 = CONCAT11(4,local_38);
        }
        uStack_2c._0_3_ = CONCAT12(1,(undefined2)uStack_2c);
        if (!bVar6) {
          _local_38 = CONCAT22(local_37._1_2_,0x202);
        }
        local_3c._0_2_ = (ushort)bVar2;
        local_3c = (uint)CONCAT12(bVar2,(ushort)local_3c);
        _local_38 = (uint3)_local_38;
        local_34 = local_34 & 0xffffff00;
        MtCmdChannelSwitch(param_1,local_3c,_local_38,local_34,local_30,uStack_2c);
        if (*(char *)(param_1 + 0x79504d) == '\0') {
          _local_38 = CONCAT11(0xf,local_38);
        }
        else {
          _local_38 = CONCAT11(3,local_38);
        }
        MtCmdSetTxRxPath(param_1,local_3c,_local_38,local_34,local_30,uStack_2c);
      } while (uVar5 < MT7915_DNL_CAL_GBAND_BW20_CH_SIZE);
    }
    MtCmdDoCalibration(param_1,1,0x8000000,0);
    uVar4 = 0x2000000;
  }
  else {
    if (iVar3 != 2) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Should not be here !\n","MtATE_DNL_Cal_Store_Proc_7915");
      return 1;
    }
    pcVar1 = "SetPartProfileParameters" + param_1;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    pcVar1 = "SetPartProfileParameters" + param_1 + 0x10;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    os_zero_mem(&local_3c,0x14);
    bVar6 = MT7915_DNL_CAL_ABAND_BW20_CH_SIZE != 0;
    *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) | 0x200;
    if (bVar6) {
      uVar5 = 0;
      do {
        uStack_2c._0_3_ = CONCAT12(1,(undefined2)uStack_2c);
        bVar6 = *(char *)(param_1 + 0x79504d) == '\0';
        if (bVar6) {
          _local_38 = CONCAT22(local_37._1_2_,0x404);
        }
        if (bVar6) {
          local_34 = (uint)local_34._1_3_ << 8;
        }
        else {
          local_34 = CONCAT31(local_34._1_3_,1);
          _local_38 = CONCAT31(CONCAT21(local_37._1_2_,2),2);
        }
        local_3c._0_2_ = (ushort)(byte)MT7915_DNL_CAL_ABAND_BW20_CH[uVar5 * 2];
        local_3c = (uint)CONCAT12(MT7915_DNL_CAL_ABAND_BW20_CH[uVar5 * 2],(ushort)local_3c);
        _local_38 = (uint3)_local_38;
        local_34._0_2_ = CONCAT11(1,(undefined1)local_34);
        MtCmdChannelSwitch(param_1,local_3c,_local_38,local_34,local_30,uStack_2c);
        if (*(char *)(param_1 + 0x79504d) == '\0') {
          _local_38 = CONCAT11(0xf,local_38);
        }
        else {
          _local_38 = CONCAT11(3,local_38);
        }
        MtCmdSetTxRxPath(param_1,local_3c,_local_38,local_34,local_30,uStack_2c);
        uVar5 = uVar5 + 1 & 0xff;
      } while (uVar5 < MT7915_DNL_CAL_ABAND_BW20_CH_SIZE);
    }
    MtCmdDoCalibration(param_1,1,0x8000000,0);
    uVar4 = 0x4000000;
  }
  MtCmdDoCalibration(param_1,1,uVar4,0);
  *(uint *)(param_1 + 0xa3ac14) = *(uint *)(param_1 + 0xa3ac14) & 0xfffffdff;
  return 1;
}

