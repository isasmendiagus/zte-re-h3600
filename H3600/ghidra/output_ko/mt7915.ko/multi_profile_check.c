// module: mt7915.ko
// function: multi_profile_check @ 0x165720
// size: 5312 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 multi_profile_check(int param_1,char *param_2)

{
  void *__src;
  undefined1 *puVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  size_t sVar7;
  size_t sVar8;
  byte bVar9;
  undefined4 uVar10;
  byte bVar11;
  uint uVar12;
  void *local_70;
  int local_6c;
  undefined1 *local_68;
  char local_61;
  undefined1 auStack_60 [24];
  undefined1 *local_48;
  undefined1 *local_44;
  undefined1 *local_40;
  undefined1 *local_3c;
  undefined1 *local_38;
  undefined1 *local_34;
  undefined1 local_30;
  
  local_70 = (void *)0x0;
  local_6c = 0;
  os_alloc_mem(param_1,&local_70,0x8000);
  if (local_70 == (void *)0x0) {
    return 1;
  }
  iVar4 = FUN_001622dc(_LANCHOR1);
  if ((iVar4 != 0) || (os_alloc_mem(param_1,&local_6c,0x8000), local_6c == 0)) {
    uVar10 = 1;
    goto LAB_00165774;
  }
  puVar5 = (undefined1 *)FUN_001622dc(s__etc_Wireless_RT2860_RT2860_5G_d_0034d5b2);
  iVar4 = local_6c;
  __src = local_70;
  if (puVar5 == (undefined1 *)0x0) {
    local_30 = 0;
    local_68 = puVar5;
    local_48 = puVar5;
    local_44 = puVar5;
    local_40 = puVar5;
    local_3c = puVar5;
    local_38 = puVar5;
    local_34 = puVar5;
    iVar6 = RTMPGetKeyParameter("DBDC_MODE",&local_48,0x19,local_70,1);
    if ((iVar6 != 0) && (cVar3 = simple_strtol(&local_48,0,10), cVar3 == '\0')) {
      if (-1 < DebugLevel) {
        printk("DBDC_MODE is not enable! Not need to merge.\n");
      }
      goto LAB_001657b4;
    }
    os_alloc_mem(param_1,&local_68,5);
    if (local_68 == (undefined1 *)0x0) goto LAB_001657b4;
    *(undefined1 **)(param_1 + 0xa7cbdc) = local_68;
    os_move_mem(param_2,__src,0x8000);
    puVar5 = local_68;
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      local_48 = (undefined1 *)0x0;
      local_44 = (undefined1 *)0x0;
      local_40 = (undefined1 *)0x0;
      local_3c = (undefined1 *)0x0;
      local_38 = (undefined1 *)0x0;
      local_34 = (undefined1 *)0x0;
      local_30 = 0;
      iVar6 = RTMPGetKeyParameter("BssidNum",&local_48,0x19,__src,1);
      if (iVar6 == 0) {
        cVar3 = '\0';
      }
      else {
        cVar3 = simple_strtol(&local_48,0,10);
      }
      iVar6 = RTMPGetKeyParameter("BssidNum",&local_48,0x19,iVar4,1);
      if (iVar6 == 0) {
        cVar2 = '\0';
      }
      else {
        cVar2 = simple_strtol(&local_48,0,10);
      }
      snprintf((char *)&local_48,0x19,"%d",(uint)(byte)(cVar2 + cVar3));
      RTMPSetKeyParameter("BssidNum",&local_48,0x19,param_2,1);
      puVar1 = local_68;
      puVar5[2] = cVar3;
      puVar5[4] = cVar2 + cVar3;
      local_61 = '\0';
      puVar5[3] = cVar2;
      memset(auStack_60,0,0x18);
      local_48 = (undefined1 *)0x0;
      local_44 = (undefined1 *)0x0;
      local_40 = (undefined1 *)0x0;
      local_3c = (undefined1 *)0x0;
      local_38 = (undefined1 *)0x0;
      local_34 = (undefined1 *)0x0;
      local_30 = 0;
      iVar6 = RTMPGetKeyParameter("MacAddress",&local_61,0x19,iVar4,1);
      if (iVar6 != 0) {
        snprintf((char *)&local_48,0x19,"MacAddress%d",(uint)(byte)puVar1[2]);
        RTMPAddKeyParameter(&local_48,&local_61,0x19,param_2);
      }
      if (puVar1[3] != '\0') {
        uVar12 = 1;
        do {
          snprintf((char *)&local_48,0x19,"MacAddress%d",uVar12);
          iVar6 = RTMPGetKeyParameter(&local_48,&local_61,0x19,iVar4,1);
          if (iVar6 != 0) {
            snprintf((char *)&local_48,0x19,"MacAddress%d",uVar12 + (byte)puVar1[2] & 0xff);
            RTMPAddKeyParameter(&local_48,&local_61,0x19,param_2);
          }
          uVar12 = uVar12 + 1 & 0xff;
        } while (uVar12 <= (byte)puVar1[3]);
      }
      iVar6 = RTMPGetKeyParameter("ApcliMacAddress",&local_61,0x19,iVar4,1);
      if (iVar6 != 0) {
        local_48 = (undefined1 *)0x6c637041;
        local_44 = (undefined1 *)0x63614d69;
        local_40 = (undefined1 *)0x72646441;
        local_3c = (undefined1 *)0x31737365;
        local_38 = (undefined1 *)((uint)local_38 & 0xffffff00);
        RTMPAddKeyParameter(&local_48,&local_61,0x19,param_2);
      }
      FUN_00162424(puVar1,1,&_LC128,__src,iVar4,param_2);
      FUN_001633b8(puVar1,"FragThreshold",__src,iVar4,param_2,2);
      FUN_00162680("DLSCapable",__src,iVar4,param_2);
      FUN_001633b8(puVar1,"WirelessMode",__src,iVar4,param_2,2);
      FUN_0016252c(puVar1,__src,iVar4,param_2);
      FUN_001628d0(__src,iVar4,param_2);
      FUN_00162680("AutoChannelSelect",__src,iVar4,param_2);
      FUN_00162680("AutoChannelSkipList",__src,iVar4,param_2);
      FUN_00162680("ACSCheckTime",__src,iVar4,param_2);
      FUN_001633b8(puVar1,"IEEE8021X",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"PreAuth",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"AuthMode",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"EncrypType",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"RekeyMethod",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"RekeyInterval",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"PMKCachePeriod",__src,iVar4,param_2,2);
      FUN_00162424(puVar1,1,"WPAPSK",__src,iVar4,param_2);
      FUN_001633b8(puVar1,"DefaultKeyID",__src,iVar4,param_2,2);
      FUN_0016278c(puVar1,__src,iVar4,param_2);
      FUN_00162424(puVar1,0,"AccessPolicy",__src,iVar4,param_2);
      FUN_00162424(puVar1,0,"AccessControlList",__src,iVar4,param_2);
      FUN_001633b8(puVar1,"RADIUS_Server",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"RADIUS_Port",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"RADIUS_Key",__src,iVar4,param_2,2);
      FUN_00163fd4(puVar1,__src,iVar4,param_2);
      FUN_001633b8(puVar1,"EAPifname",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"PreAuthifname",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"PMFMFPC",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"PMFMFPR",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"PMFSHA256",__src,iVar4,param_2,2);
      FUN_00162424(puVar1,1,"PWDID",__src,iVar4,param_2);
      FUN_001633b8(puVar1,"PWDIDR",__src,iVar4,param_2,2);
      FUN_00162680("WmmCapable",__src,iVar4,param_2);
      FUN_00162680("NoForwarding",__src,iVar4,param_2);
      FUN_001633b8(puVar1,"StationKeepAlive",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"HideSSID",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"HT_EXTCHA",__src,iVar4,param_2,2);
      FUN_00162680("HT_TxStream",__src,iVar4,param_2);
      FUN_00162680("HT_RxStream",__src,iVar4,param_2);
      FUN_00162680("HT_MCS",__src,iVar4,param_2);
      FUN_001633b8(puVar1,"HT_BW",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"HT_STBC",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"HT_LDPC",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"HT_AMSDU",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"AMSDU_NUM",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"PPDUTxType",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"OFDMA",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"NumUsersOFDMA",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"NonTxBSSIndex",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"HE_TXOP_RTS_THLD",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"FixedMcs",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"VHT_STBC",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"VHT_LDPC",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"HeLdpc",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"FgiFltf",__src,iVar4,param_2,2);
      FUN_00162680("MbssMaxStaNum",__src,iVar4,param_2);
      FUN_00162680("APSDCapable",__src,iVar4,param_2);
      FUN_0016519c(puVar1,__src,iVar4,param_2);
      FUN_00165438(puVar1,__src,iVar4,param_2);
      local_61 = '\0';
      memset(auStack_60,0,0x18);
      iVar6 = RTMPGetKeyParameter("AckPolicy",&local_48,0x20,__src,1);
      if ((iVar6 != 0) && (puVar1[2] != '\0')) {
        uVar12 = 0;
        do {
          snprintf(&local_61,0x19,"APAckPolicy%d",uVar12);
          uVar12 = uVar12 + 1 & 0xff;
          RTMPSetKeyParameter(&local_61,&local_48,0x20,param_2,1);
        } while (uVar12 < (byte)puVar1[2]);
      }
      iVar6 = RTMPGetKeyParameter("AckPolicy",&local_48,0x20,iVar4,1);
      if ((iVar6 != 0) && (puVar1[3] != '\0')) {
        bVar11 = 0;
        do {
          bVar9 = bVar11 + puVar1[2];
          bVar11 = bVar11 + 1;
          snprintf(&local_61,0x19,"APAckPolicy%d",(uint)bVar9);
          RTMPSetKeyParameter(&local_61,&local_48,0x20,param_2,1);
        } while (bVar11 < (byte)puVar1[3]);
      }
      FUN_00163f20(iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Min_Rate",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Max_Rate",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Min_Ratio",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Max_Ratio",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Airtime_Ctrl_En",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Rate_Ctrl_En",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Min_Rate_Bucket_Size",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Max_Rate_Bucket_Size",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Min_Airtime_Bucket_Size",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Max_Airtime_Bucket_Size",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Backlog",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_Max_Wait_Time",__src,iVar4,param_2);
      FUN_00162a14(puVar1,"VOW_Group_DWRR_Quantum",__src,iVar4,param_2);
      FUN_00162bd0(puVar1,__src,iVar4,param_2);
      FUN_001633b8(puVar1,"ETxBfEnCond",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"ITxBfEn",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"BfSmthIntlBbypass",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"MuOfdmaDlEnable",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"MuOfdmaUlEnable",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"MuMimoDlEnable",__src,iVar4,param_2,2);
      FUN_001633b8(puVar1,"MuMimoUlEnable",__src,iVar4,param_2,2);
      FUN_00162680("SREnable",__src,iVar4,param_2);
      FUN_00162680("SRMode",__src,iVar4,param_2);
      FUN_00162680("SRSDEnable",__src,iVar4,param_2);
      FUN_00162680("PPEnable",__src,iVar4,param_2);
      FUN_001633b8(puVar1,"Dot11vMbssid",__src,iVar4,param_2,0);
      FUN_00162680("EDCCAEnable",__src,iVar4,param_2);
      iVar6 = FUN_0016444c(__src,iVar4,param_2);
      if ((iVar6 != 0) || (iVar6 = FUN_00163b30(local_68,__src,iVar4,param_2), iVar6 != 0))
      goto LAB_001657b4;
    }
    FUN_001633b8(local_68,"HT_GI",__src,iVar4,param_2,2);
    puVar5 = local_68;
    FUN_001633b8(local_68,"RTSPktThreshold",__src,iVar4,param_2,2);
    FUN_001633b8(puVar5,"RTSThreshold",__src,iVar4,param_2,2);
    FUN_001633b8(puVar5,"HT_PROTECT",__src,iVar4,param_2,2);
    FUN_001633b8(local_68,"FragThreshold",__src,iVar4,param_2,2);
    FUN_001633b8(local_68,"HT_MpduDensity",__src,iVar4,param_2,2);
    FUN_001633b8(local_68,"HT_OpMode",__src,iVar4,param_2,2);
    puVar5 = local_68;
    FUN_001633b8(local_68,"HT_BADecline",__src,iVar4,param_2,2);
    FUN_001633b8(puVar5,"HT_AutoBA",__src,iVar4,param_2,2);
    FUN_001633b8(puVar5,"HT_BAWinSize",__src,iVar4,param_2,2);
    puVar5 = local_68;
    FUN_001633b8(local_68,"BeaconPeriod",__src,iVar4,param_2,2);
    FUN_001633b8(puVar5,"DtimPeriod",__src,iVar4,param_2,2);
    puVar5 = local_68;
    FUN_001633b8(local_68,"McastPhyMode",__src,iVar4,param_2,2);
    FUN_001633b8(puVar5,"McastMcs",__src,iVar4,param_2,2);
    iVar6 = FUN_001636c4(local_68,__src,iVar4,param_2);
    if (iVar6 != 0) goto LAB_001657b4;
    FUN_00162680("IgmpSnEnable",__src,iVar4,param_2);
    FUN_00162680("PowerEnhance",__src,iVar4,param_2);
    FUN_00162680("AntennaGain",__src,iVar4,param_2);
    FUN_00162680("CombinedGain",__src,iVar4,param_2);
    FUN_00162680("WorkMode",__src,iVar4,param_2);
    FUN_00162680("SKUenable",__src,iVar4,param_2);
    FUN_00162680("PERCENTAGEenable",__src,iVar4,param_2);
    FUN_00162680("BFBACKOFFenable",__src,iVar4,param_2);
    FUN_00162680("TxPower",__src,iVar4,param_2);
    FUN_00162680("PowerUpCck",__src,iVar4,param_2);
    FUN_00162680("PowerUpOfdm",__src,iVar4,param_2);
    FUN_00162680("PowerUpHT20",__src,iVar4,param_2);
    FUN_00162680("PowerUpHT40",__src,iVar4,param_2);
    FUN_00162680("PowerUpVHT20",__src,iVar4,param_2);
    FUN_00162680("PowerUpVHT40",__src,iVar4,param_2);
    FUN_00162680("PowerUpVHT80",__src,iVar4,param_2);
    FUN_00162680("PowerUpVHT160",__src,iVar4,param_2);
    FUN_00162680("PowerUpRU26",__src,iVar4,param_2);
    FUN_00162680("PowerUpRU52",__src,iVar4,param_2);
    FUN_00162680("PowerUpRU106",__src,iVar4,param_2);
    FUN_00162680("PowerUpRU242",__src,iVar4,param_2);
    FUN_00162680("PowerUpRU484",__src,iVar4,param_2);
    FUN_00162680("PowerUpRU996",__src,iVar4,param_2);
    FUN_00162680("PowerUpRU996X2",__src,iVar4,param_2);
    FUN_00162680("ApMWDS",__src,iVar4,param_2);
    FUN_00162680("ApCliMWDS",__src,iVar4,param_2);
    FUN_00162680("RRMEnable",__src,iVar4,param_2);
    *local_68 = 1;
    local_68[1] = 1;
    if (0 < DebugLevel) {
      printk("multi-profile merge success, en:%d,pf1_num:%d,pf2_num:%d,total:%d\n",*local_68,
             local_68[2],local_68[3],local_68[4]);
    }
    if ((char)DAT_0034d5e4 == '\0') {
      sVar7 = FUN_00164b60();
      strncat((char *)&DAT_0034d5e4,_LANCHOR1,sVar7);
      sprintf((char *)&DAT_0034d5e4,"%sDBDC_card%d.dat",&DAT_0034d5e4,0);
    }
    if (0 < DebugLevel) {
      uVar10 = FUN_00164b60();
      printk("Open file \"%s\" to store DBDC cfg! (%d)\n",&DAT_0034d5e4,uVar10);
    }
    os_file_open(&local_48,&DAT_0034d5e4,0x41,0);
    if (local_38 == (undefined1 *)0x0) {
      if (param_2 != (char *)0x0) {
        sVar8 = strlen(param_2);
        sVar7 = sVar8;
        if (0x8000 < sVar8) {
          if (DebugLevel < 0) {
            sVar7 = 0x8000;
          }
          else {
            sVar7 = 0x8000;
            printk("ERROR!! exceeded buffer size %d (> %d)!\n",sVar8);
          }
        }
        iVar4 = os_file_write(local_48,local_44,local_40,local_3c,local_38,local_34,param_2,sVar7);
        if (iVar4 < 1) {
          if (-1 < DebugLevel) {
            printk("Write file \"%s\" failed(errCode=%d)!\n",&DAT_0034d5e4);
          }
        }
        else if (0 < DebugLevel) {
          printk("Write file \"%s\" success (size=%d)!\n",&DAT_0034d5e4,sVar7);
        }
      }
      iVar4 = os_file_close(local_48,local_44,local_40,local_3c,local_38,local_34);
      if ((iVar4 != 0) && (-1 < DebugLevel)) {
        printk("Close file \"%s\" failed(errCode=%d)!\n",&DAT_0034d5e4,1);
      }
    }
    else if (-1 < DebugLevel) {
      printk("Open file \"%s\" failed!\n",&DAT_0034d5e4);
    }
    uVar10 = 0;
  }
  else {
LAB_001657b4:
    uVar10 = 1;
  }
  os_free_mem(local_6c);
LAB_00165774:
  os_free_mem(local_70);
  return uVar10;
}

