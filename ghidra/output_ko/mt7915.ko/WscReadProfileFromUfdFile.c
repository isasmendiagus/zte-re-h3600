// module: mt7915.ko
// function: WscReadProfileFromUfdFile @ 0x200748
// size: 1160 bytes
//

undefined4 WscReadProfileFromUfdFile(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  char *pcVar6;
  int local_70;
  undefined1 auStack_6c [12];
  undefined1 auStack_60 [64];
  
  iVar3 = 0;
  local_70 = 0;
  memset(auStack_60,0,0x40);
  if (param_3 == 0) {
    if (2 < DebugLevel) {
      printk("--> %s: pUfdFileName is NULL\n","WscReadProfileFromUfdFile");
      return 0;
    }
    return 0;
  }
  RtmpOSFSInfoChange(auStack_6c,1);
  uVar1 = RtmpOSFileOpen(param_3,0,0);
  if ((uVar1 == 0) || (0xfffff000 < uVar1)) {
    if (2 < DebugLevel) {
      printk("--> %s: Error opening file %s\n","WscReadProfileFromUfdFile",param_3);
    }
    RtmpOSFSInfoChange(auStack_6c,0);
    return 0;
  }
  while (iVar2 = RtmpOSFileRead(uVar1,auStack_60,0x40), 0 < iVar2) {
    iVar3 = iVar3 + iVar2;
  }
  os_alloc_mem(param_1,&local_70,iVar3 + 1);
  if (local_70 == 0) {
    RtmpOSFileClose(uVar1);
    RtmpOSFSInfoChange(auStack_6c,0);
    if (DebugLevel < 3) {
      return 0;
    }
    printk("pXmlData mem alloc fail. (fileLen = %d)\n",iVar3);
    return 0;
  }
  RTMPZeroMemory(local_70,iVar3 + 1);
  RtmpOSFileSeek(uVar1,0);
  iVar2 = RtmpOSFileRead(uVar1,local_70,iVar3);
  RtmpOSFileClose(uVar1);
  if (iVar2 != iVar3) {
    if (2 < DebugLevel) {
      printk("RtmpOSFileRead fail, fileLen = %d\n",iVar3);
    }
    RtmpOSFSInfoChange(auStack_6c,0);
LAB_00200844:
    if (local_70 != 0) {
      os_free_mem();
      return 0;
    }
    return 0;
  }
  RtmpOSFSInfoChange(auStack_6c,0);
  if (2 < DebugLevel) {
    printk("WscReadProfileFromUfdFile\n");
  }
  iVar3 = WscPassXmlDeclare(&local_70);
  if (iVar3 == 0) goto LAB_00200844;
  iVar3 = param_1 + param_2 * 0x5834 + 4;
  pcVar6 = "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
           + iVar3 + 4;
  iVar2 = WscGetXmlSSID(local_70,pcVar6);
  if (iVar2 != 0) {
    if (2 < DebugLevel) {
      printk("SSID = %s(%d)\n",
             "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
             + iVar3 + 8,
             *(undefined4 *)
              (
              "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
              + param_1 + param_2 * 0x5834 + 8));
    }
    iVar3 = WscGetXmlAuth(local_70,"@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                                   + param_1 + param_2 * 0x5834 + 0x2c);
    if (iVar3 != 0) {
      if (2 < DebugLevel) {
        printk("Credential.AuthType = 0x%04x\n",
               *(undefined2 *)
                (
                "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                + param_1 + param_2 * 0x5834 + 0x2c));
      }
      iVar3 = WscGetXmlEncr(local_70,"@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                                     + param_1 + param_2 * 0x5834 + 0x2e);
      if (iVar3 != 0) {
        if (2 < DebugLevel) {
          printk("Credential.EncrType = 0x%04x\n",
                 *(undefined2 *)
                  (
                  "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                  + param_1 + param_2 * 0x5834 + 0x2e));
        }
        iVar3 = param_1 + param_2 * 0x5834;
        pcVar5 = "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                 + iVar3 + 0x30;
        (
        "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
        + iVar3 + 0x70)[0] = '\0';
        (
        "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
        + iVar3 + 0x70)[1] = '\0';
        RTMPZeroMemory(pcVar5,0x40);
        iVar2 = WscGetXmlKey(local_70,pcVar5,
                             "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                             + param_1 + param_2 * 0x5834 + 0x70);
        if (iVar2 != 0) {
          if (2 < DebugLevel) {
            printk("Credential.Key = %s (%d)\n",pcVar5,
                   *(undefined2 *)
                    (
                    "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                    + iVar3 + 0x70));
          }
          iVar3 = WscGetXmlKeyIndex(local_70,"@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                                             + param_1 + param_2 * 0x5834 + 0x78);
          if (iVar3 == 0) {
LAB_00200af0:
            if (2 < DebugLevel) {
              printk("WscReadProfileFromUfdFile OK\n");
            }
          }
          else if (2 < DebugLevel) {
            printk("pCredential->KeyIndex = %d\n",
                   "@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
                   [param_1 + param_2 * 0x5834 + 0x78]);
            goto LAB_00200af0;
          }
          uVar4 = 1;
          WscWriteConfToPortCfg
                    (param_1,"4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                             + param_2 * 0x5834 + param_1 + 0x2b,pcVar6);
          *(char *)(param_1 + 0x794b18) = (char)param_2;
          RtmpOsTaskWakeUp(param_1 + 0x794ae8);
          goto LAB_00200aac;
        }
      }
    }
  }
  uVar4 = 0;
LAB_00200aac:
  if (local_70 == 0) {
    return uVar4;
  }
  os_free_mem(local_70);
  return uVar4;
}

