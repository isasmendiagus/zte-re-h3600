// module: mt7915.ko
// function: WscWriteProfileToUfdFile @ 0x200bd0
// size: 1232 bytes
//

undefined4 WscWriteProfileToUfdFile(int param_1,int param_2,int param_3)

{
  short sVar1;
  uint uVar2;
  size_t sVar3;
  bool bVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  undefined1 auStack_64 [15];
  undefined1 auStack_55 [16];
  undefined1 auStack_45 [37];
  
  if (param_3 == 0) {
    if (DebugLevel < 3) {
      return 0;
    }
    printk("--> %s: pUfdFileName is NULL\n","WscWriteProfileToUfdFile");
    return 0;
  }
  RtmpOSFSInfoChange(auStack_64,1);
  uVar2 = RtmpOSFileOpen(param_3,0x241,0);
  if ((uVar2 == 0) || (0xfffff000 < uVar2)) {
    if (2 < DebugLevel) {
      printk("--> %s: Error opening file %s\n","WscWriteProfileToUfdFile",param_3);
    }
    RtmpOSFSInfoChange(auStack_64,0);
    return 0;
  }
  iVar9 = param_1 + param_2 * 0x5834;
  WscCreateProfileFromCfg
            (param_1,0,
             "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
             + iVar9 + 0x2b,
             "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
             + iVar9);
  pcVar7 = 
  "<?xml version=\"1.0\"?>\n<wirelessProfile>\n\t<config>\n\t\t<configId>CFG_GUID</configId>\n\t\t<configAuthorId>CFG_AP_GUID</configAuthorId>\n\t\t<configAuthor>Ralink WPS AP</configAuthor>\n\t</config>\n\t<ssid xml:space=\"preserve\">CFG_SSID</ssid>\n\t<connectionType>ESS</connectionType>\n\t<channel2Dot4>0</channel2Dot4>\n\t<channel5Dot0>0</channel5Dot0>\n\t<primaryProfile>\n\t\t<authentication>CFG_AUTH</authentication>\n\t\t<encryption>CFG_ENCR</encryption>\n\t\t<networkKey xml:space=\"preserve\">CFG_KEY</networkKey>\n\t\t<keyProvidedAutomatically>0</keyProvidedAutomatically>\n\t\t<ieee802Dot1xEnabled>0</ieee802Dot1xEnabled>\n\t</primaryProfile>\n</wirelessProfile>\n"
  ;
  WscGenerateUUID(param_1,auStack_55,auStack_45,param_2,1,0);
  iVar9 = rtstrstr("<?xml version=\"1.0\"?>\n<wirelessProfile>\n\t<config>\n\t\t<configId>CFG_GUID</configId>\n\t\t<configAuthorId>CFG_AP_GUID</configAuthorId>\n\t\t<configAuthor>Ralink WPS AP</configAuthor>\n\t</config>\n\t<ssid xml:space=\"preserve\">CFG_SSID</ssid>\n\t<connectionType>ESS</connectionType>\n\t<channel2Dot4>0</channel2Dot4>\n\t<channel5Dot0>0</channel5Dot0>\n\t<primaryProfile>\n\t\t<authentication>CFG_AUTH</authentication>\n\t\t<encryption>CFG_ENCR</encryption>\n\t\t<networkKey xml:space=\"preserve\">CFG_KEY</networkKey>\n\t\t<keyProvidedAutomatically>0</keyProvidedAutomatically>\n\t\t<ieee802Dot1xEnabled>0</ieee802Dot1xEnabled>\n\t</primaryProfile>\n</wirelessProfile>\n"
                   ,"CFG_GUID");
  if (iVar9 != 0) {
    pcVar7 = (char *)(iVar9 + 8);
    RtmpOSFileWrite(uVar2,
                    "<?xml version=\"1.0\"?>\n<wirelessProfile>\n\t<config>\n\t\t<configId>CFG_GUID</configId>\n\t\t<configAuthorId>CFG_AP_GUID</configAuthorId>\n\t\t<configAuthor>Ralink WPS AP</configAuthor>\n\t</config>\n\t<ssid xml:space=\"preserve\">CFG_SSID</ssid>\n\t<connectionType>ESS</connectionType>\n\t<channel2Dot4>0</channel2Dot4>\n\t<channel5Dot0>0</channel5Dot0>\n\t<primaryProfile>\n\t\t<authentication>CFG_AUTH</authentication>\n\t\t<encryption>CFG_ENCR</encryption>\n\t\t<networkKey xml:space=\"preserve\">CFG_KEY</networkKey>\n\t\t<keyProvidedAutomatically>0</keyProvidedAutomatically>\n\t\t<ieee802Dot1xEnabled>0</ieee802Dot1xEnabled>\n\t</primaryProfile>\n</wirelessProfile>\n"
                    ,iVar9 + -0x311b64);
    RtmpOSFileWrite(uVar2,auStack_45,0x25);
  }
  iVar9 = rtstrstr(pcVar7,"CFG_AP_GUID");
  pcVar8 = pcVar7;
  if (iVar9 != 0) {
    pcVar8 = (char *)(iVar9 + 0xb);
    RtmpOSFileWrite(uVar2,pcVar7,iVar9 - (int)pcVar7);
    RtmpOSFileWrite(uVar2,"IF(ra0) Set_WscPinCode_Proc::(PinCode=%d)\n" +
                          param_2 * 0x5834 + param_1 + 0x14,0x25);
  }
  iVar9 = rtstrstr(pcVar8,"CFG_SSID");
  pcVar7 = pcVar8;
  if (iVar9 != 0) {
    pcVar7 = (char *)(iVar9 + 8);
    RtmpOSFileWrite(uVar2,pcVar8,iVar9 - (int)pcVar8);
    iVar9 = param_1 + param_2 * 0x5834;
    RtmpOSFileWrite(uVar2,"@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                          + iVar9 + 0xc,
                    *(undefined4 *)
                     (
                     "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                     + iVar9 + 8));
  }
  iVar9 = rtstrstr(pcVar7,"CFG_AUTH");
  if (iVar9 == 0) {
LAB_00200e38:
    iVar9 = rtstrstr(pcVar7,"CFG_ENCR");
    if (iVar9 == 0) {
LAB_00200f24:
      iVar9 = rtstrstr(pcVar7,"CFG_KEY");
      pcVar8 = pcVar7;
      if (iVar9 != 0) {
        param_1 = param_1 + param_2 * 0x5834;
        if (*(short *)(
                      "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                      + param_1 + 0x2e) == 1) {
          RtmpOSFileWrite(uVar2,"</encryption>",0xd);
          pcVar8 = (char *)(iVar9 + 0x15);
          RtmpOSFileWrite(uVar2,&_LC43,1);
        }
        else {
          pcVar8 = (char *)(iVar9 + 7);
          RtmpOSFileWrite(uVar2,pcVar7,iVar9 - (int)pcVar7);
          RtmpOSFileWrite(uVar2,"@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                                + param_1 + 0x30,
                          *(undefined2 *)
                           (
                           "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                           + param_1 + 0x70));
        }
      }
      uVar6 = 1;
      sVar3 = strlen(pcVar8);
      RtmpOSFileWrite(uVar2,pcVar8,sVar3);
      goto LAB_00200df8;
    }
    RtmpOSFileWrite(uVar2,pcVar7,iVar9 - (int)pcVar7);
    DAT_005f4ac0 = &DAT_005dfe20;
    if (DAT_005dfe20 != (char *)0x0) {
      bVar4 = false;
      pcVar7 = DAT_005dfe20;
      do {
        if (*(short *)(DAT_005f4ac0 + 1) ==
            *(short *)(
                      "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                      + param_2 * 0x5834 + param_1 + 0x2e)) {
          sVar3 = strlen(pcVar7);
          RtmpOSFileWrite(uVar2,pcVar7,sVar3);
          bVar4 = true;
        }
        puVar5 = DAT_005f4ac0 + 2;
        pcVar7 = (char *)DAT_005f4ac0[2];
        DAT_005f4ac0 = puVar5;
      } while (pcVar7 != (char *)0x0);
      if (bVar4) {
        pcVar7 = (char *)(iVar9 + 8);
        goto LAB_00200f24;
      }
    }
    if (2 < DebugLevel) {
      uVar6 = 0;
      printk("--> %s: Unknow Encr Type(=%x)\n","WscWriteProfileToUfdFile",
             *(undefined2 *)
              (
              "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
              + param_2 * 0x5834 + param_1 + 0x2e));
      goto LAB_00200df8;
    }
  }
  else {
    RtmpOSFileWrite(uVar2,pcVar7,iVar9 - (int)pcVar7);
    _LANCHOR1 = &_LANCHOR0;
    puVar5 = _LANCHOR1;
    if (_LANCHOR0 != (char *)0x0) {
      _LANCHOR1 = &_LANCHOR0;
      pcVar8 = _LANCHOR0;
      sVar1 = DAT_005dfdec;
      while (sVar1 != *(short *)(
                                "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                                + param_2 * 0x5834 + param_1 + 0x2c)) {
        puVar5 = _LANCHOR1 + 2;
        pcVar8 = (char *)*puVar5;
        if (pcVar8 == (char *)0x0) goto LAB_00200de0;
        sVar1 = *(short *)(_LANCHOR1 + 3);
        _LANCHOR1 = puVar5;
      }
      pcVar7 = (char *)(iVar9 + 8);
      sVar3 = strlen(pcVar8);
      RtmpOSFileWrite(uVar2,pcVar8,sVar3);
      goto LAB_00200e38;
    }
LAB_00200de0:
    _LANCHOR1 = puVar5;
    if (2 < DebugLevel) {
      uVar6 = 0;
      printk("--> %s: Unknow Auth Type(=%x)\n","WscWriteProfileToUfdFile",
             *(undefined2 *)
              (
              "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
              + param_2 * 0x5834 + param_1 + 0x2c));
      goto LAB_00200df8;
    }
  }
  uVar6 = 0;
LAB_00200df8:
  RtmpOSFileClose(uVar2);
  RtmpOSFSInfoChange(auStack_64,0);
  return uVar6;
}

