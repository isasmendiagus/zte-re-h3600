// module: mt7915.ko
// function: MtATE_DPD_Cal_Store_Proc_7915 @ 0x28b4b0
// size: 1240 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 MtATE_DPD_Cal_Store_Proc_7915(int param_1,int param_2)

{
  char *pcVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  ushort local_3e;
  undefined1 local_3c [2];
  undefined1 uStack_3a;
  undefined1 uStack_39;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  local_34 = CONCAT22(local_34._2_2_,CONCAT11(local_34._1_1_,(undefined1)local_34));
  local_38 = CONCAT13(local_38._3_1_,
                      CONCAT12(local_38._2_1_,CONCAT11(local_38._1_1_,(undefined1)local_38)));
  _local_3c = CONCAT13(uStack_39,CONCAT12(uStack_3a,CONCAT11(local_3c[1],local_3c[0])));
  local_3e = 0;
  if (("cp_support_is_enabled"[param_1 + 4] - 2U & 0xfd) != 0) {
    if (-1 < DebugLevel) {
      printk("%s: Currently not in FLASH or BIN MODE,return.\n","MtATE_DPD_Cal_Store_Proc_7915");
    }
    return 0;
  }
  "RTMPSetSTAPassPhrase"[param_1 + 3] = '\x01';
  if (param_2 == 0) {
    pcVar1 = "RTMPSetSTAPassPhrase" + param_1 + 0x14;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    RTMPZeroMemory(*(undefined4 *)("RTMPSetSTAPassPhrase" + param_1 + 0x10),0xd800);
    if ("cp_support_is_enabled"[param_1 + 4] == '\x02') {
      rtmp_ee_flash_read(param_1,0x62,&local_3e);
      local_3e = local_3e & 0xfff9;
      rtmp_ee_flash_write(param_1,0x62);
    }
  }
  else if (param_2 == 1) {
    MtATE_Dump_DPD_PreCal_7915();
  }
  else if (param_2 == 2) {
    uVar6 = *(undefined4 *)("RTMPSetSTAPassPhrase" + param_1 + 0x10);
    pcVar1 = "RTMPSetSTAPassPhrase" + param_1 + 0x14;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    RTMPZeroMemory(uVar6,0xd800);
    __memzero(local_3c,0x14);
    if (MT7915_DPD_FLATNESS_ABAND_BW20_CH_SIZE != 0) {
      uVar7 = 0;
      cVar3 = '\0';
      cVar4 = '\0';
      do {
        uVar5 = local_38 >> 0x10;
        local_34 = CONCAT22(local_34._2_2_,0x101);
        _local_3c = (uint3)(byte)MT7915_DPD_FLATNESS_ABAND_BW20_CH[uVar7 * 2] << 0x10;
        _local_3c = CONCAT31(_local_3c >> 8,MT7915_DPD_FLATNESS_ABAND_BW20_CH[uVar7 * 2]);
        if (*(char *)(param_1 + 0x79504d) == '\0') {
          local_38._0_2_ = 0xf0f;
          local_34 = local_34 & 0xffffff00;
        }
        else {
          cVar3 = "rtmp_read_vow_parms_from_file"[param_1];
          local_38._0_2_ = 0xc0c;
          cVar4 = "rtmp_read_vow_parms_from_file"[param_1 + 1];
          "rtmp_read_vow_parms_from_file"[param_1] = '\f';
          "rtmp_read_vow_parms_from_file"[param_1 + 1] = '\f';
        }
        local_38 = CONCAT22((short)uVar5,(undefined2)local_38) & 0xff00ffff;
        MtCmdChannelSwitch(param_1,_local_3c,local_38,local_34,local_30,uStack_2c);
        if (*(char *)(param_1 + 0x79504d) == '\0') {
          local_38._0_2_ = 0xf0f;
        }
        else {
          local_38._0_2_ = 0xc02;
          "rtmp_read_vow_parms_from_file"[param_1] = cVar3;
          "rtmp_read_vow_parms_from_file"[param_1 + 1] = cVar4;
        }
        uVar7 = uVar7 + 1 & 0xff;
        MtCmdSetTxRxPath(param_1,_local_3c,local_38,local_34,local_30,uStack_2c);
        MtCmdDoCalibration(param_1,1,0x10000000,*(char *)(param_1 + 0x79504d) != '\0');
      } while (uVar7 < MT7915_DPD_FLATNESS_ABAND_BW20_CH_SIZE);
    }
    if ("cp_support_is_enabled"[param_1 + 4] == '\x02') {
      rtmp_ee_flash_read(param_1,0x62,&local_3e);
      local_3e = local_3e | 2;
      rtmp_ee_flash_write(param_1,0x62);
    }
  }
  else if (param_2 == 3) {
    __memzero(local_3c,0x14);
    if (MT7915_DPD_FLATNESS_GBAND_BW20_CH_SIZE != 0) {
      uVar7 = 0;
      cVar3 = '\0';
      cVar4 = '\0';
      do {
        bVar2 = *(byte *)((int)&MT7915_DPD_FLATNESS_GBAND_BW20_CH + uVar7 * 2);
        uVar5 = local_38 >> 0x10;
        local_34 = local_34 & 0xffff0000;
        _local_3c = (uint3)bVar2 << 0x10;
        _local_3c = CONCAT31(_local_3c >> 8,bVar2);
        if (*(char *)(param_1 + 0x79504d) == '\0') {
          local_38._0_2_ = 0xf0f;
        }
        else {
          cVar3 = "SetPartProfileParameters"[param_1 + 0x1a];
          local_38._0_2_ = 0x303;
          cVar4 = "SetPartProfileParameters"[param_1 + 0x1b];
          "SetPartProfileParameters"[param_1 + 0x1a] = '\x03';
          "SetPartProfileParameters"[param_1 + 0x1b] = '\x03';
        }
        local_38 = CONCAT22((short)uVar5,(undefined2)local_38) & 0xff00ffff;
        MtCmdChannelSwitch(param_1,_local_3c,local_38,local_34,local_30,uStack_2c);
        if (*(char *)(param_1 + 0x79504d) == '\0') {
          local_38._0_2_ = 0xf0f;
        }
        else {
          local_38._0_2_ = 0x302;
          "SetPartProfileParameters"[param_1 + 0x1a] = cVar3;
          "SetPartProfileParameters"[param_1 + 0x1b] = cVar4;
        }
        MtCmdSetTxRxPath(param_1,_local_3c,local_38,local_34,local_30,uStack_2c);
        MtCmdDoCalibration(param_1,1,0x10000000,0);
        uVar7 = uVar7 + 1 & 0xff;
      } while (uVar7 < MT7915_DPD_FLATNESS_GBAND_BW20_CH_SIZE);
    }
    if ("cp_support_is_enabled"[param_1 + 4] == '\x02') {
      rtmp_ee_flash_read(param_1,0x62,&local_3e);
      local_3e = local_3e | 4;
      rtmp_ee_flash_write(param_1,0x62);
    }
  }
  else {
    if (DebugLevel < 0) goto LAB_0028b53c;
    printk("%s: Should not be here !\n","MtATE_DPD_Cal_Store_Proc_7915");
  }
  if (-1 < DebugLevel) {
    printk("%s: op=%d, 0x%2x=%d\n","MtATE_DPD_Cal_Store_Proc_7915",param_2,0x62,local_3e);
  }
LAB_0028b53c:
  "RTMPSetSTAPassPhrase"[param_1 + 3] = '\0';
  return 1;
}

