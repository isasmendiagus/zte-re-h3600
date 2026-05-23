// module: mt7915.ko
// function: Set_Fixed_Rate_WO_STA_Proc @ 0x1db828
// size: 896 bytes
//

undefined4 Set_Fixed_Rate_WO_STA_Proc(undefined4 param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  undefined4 local_40;
  uint local_3c;
  uint local_38;
  int local_34;
  uint local_30;
  undefined1 local_29 [2];
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  if (param_2 == (char *)0x0) {
    uVar2 = 0;
    goto LAB_001db8fc;
  }
  iVar1 = sscanf(param_2,"%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",&local_54,&local_50,&local_4c,&local_48,
                 &local_44,&local_40,&local_3c,&local_38,&local_34,&local_30);
  if (0 < DebugLevel) {
    printk("%s():WCID = %d, Mode = %d, BW = %d, MCS = %d, VhtNss = %d\n\t\t\t\tSGI = %d, Preamble = %d, STBC = %d, LDPC = %d, SpeEn = %d\n"
           ,"Set_Fixed_Rate_WO_STA_Proc",local_54,local_50,local_4c,local_48,local_44,local_40,
           local_3c,local_38,local_34,local_30);
  }
  if (iVar1 != 10) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Input format Error!\n");
    goto LAB_001db95c;
  }
  if (4 < local_50) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Unknown Mode!\n");
    goto LAB_001db95c;
  }
  if (3 < local_4c) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Unknown BW!\n");
    goto LAB_001db95c;
  }
  if (local_50 == 0) {
    if (3 < local_48) {
LAB_001dba80:
      if (DebugLevel < 0) {
        return 0;
      }
      printk("Unknown MCS!\n");
LAB_001db95c:
      if (-1 < DebugLevel) {
        printk(
              "iwpriv ra0 set FixedRate=[WCID]-[Mode]-[BW]-[MCS]-[VhtNss]-[SGI]-[Preamble]-[STBC]-[LDPC]-[SPE_EN]\n"
              );
        if (-1 < DebugLevel) {
          printk("[WCID]Wireless Client ID\n");
          if (DebugLevel < 0) {
            return 0;
          }
          printk("[Mode]CCK=0, OFDM=1, HT=2, GF=3, VHT=4\n");
          if (DebugLevel < 0) {
            return 0;
          }
          printk("[BW]BW20=0, BW40=1, BW80=2,BW160=3\n");
          if (DebugLevel < 0) {
            return 0;
          }
          printk("[MCS]CCK=0~4, OFDM=0~7, HT=0~32, VHT=0~9\n");
        }
        if ((-1 < DebugLevel) && (printk("[VhtNss]VHT=1~4, Other=ignore\n"), -1 < DebugLevel)) {
          printk("[Preamble]Long=0, Other=Short\n");
        }
      }
      return 0;
    }
  }
  else if (local_50 - 1 < 2) {
    if (0x20 < local_48) goto LAB_001dba80;
  }
  else if (local_50 == 4) {
    if (9 < local_48) goto LAB_001dba80;
    if (4 < local_44) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("Unknown VhtNss!\n");
      goto LAB_001db95c;
    }
  }
  os_zero_mem(local_29,9);
  if (local_34 != 0) {
    local_24 = 1;
  }
  local_3c = (uint)(local_3c == 0);
  local_38 = raStbcSettingCheck(local_38 & 0xff,local_50 & 0xff,local_48 & 0xff,local_44 & 0xff,0,0)
  ;
  local_27 = (undefined1)local_38;
  local_29[0] = (undefined1)local_50;
  local_26 = (undefined1)local_40;
  local_25 = (undefined1)local_4c;
  local_23 = (undefined1)local_48;
  local_22 = (undefined1)local_44;
  CmdRaFixRateUpdateWoSta(param_1,local_54 & 0xffff,local_29,local_30 & 0xff,local_3c & 0xff);
  uVar2 = local_54 & 0xffff;
LAB_001db8fc:
  asic_dump_wtbl_info(param_1,uVar2);
  return 1;
}

