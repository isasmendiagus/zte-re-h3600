// module: mt7915.ko
// function: Show_Pad_Proc @ 0x15e0a4
// size: 2508 bytes
//

undefined4 Show_Pad_Proc(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  int *piVar4;
  char *pcVar5;
  int iVar6;
  
  if (0x1f < *(uint *)(*param_1 + 0x3c)) {
    return 0;
  }
  iVar1 = HcGetBandByWdev(param_1 + *(uint *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
  if ((-1 < DebugLevel) &&
     (printk("bMAPEnable = %d\n",*(undefined1 *)((int)param_1 + 0xa7cbfa)), -1 < DebugLevel)) {
    printk("MBSSID.wdev.MAPCfg.DevOwnRole = ");
  }
  puVar3 = (undefined1 *)((int)param_1 + 0x2bb1a5);
  iVar2 = DebugLevel;
  do {
    if (-1 < iVar2) {
      printk("0x%x ",*puVar3);
      iVar2 = DebugLevel;
    }
    puVar3 = puVar3 + 0x5834;
  } while (puVar3 != (undefined1 *)((int)param_1 + 0x2d6aa9));
  if (-1 < iVar2) {
    printk(&_LC45);
    if (DebugLevel < 0) {
LAB_0015e8c4:
      if (DebugLevel < 0) {
LAB_0015e95c:
        iVar2 = DebugLevel;
        if ((-1 < DebugLevel) &&
           (printk("ApCfg.StaIdleTimeout = %u\n",param_1[0xdae43]), iVar2 = DebugLevel,
           -1 < DebugLevel)) {
          printk("ApCfg.AutoChannelAlg = %u\n",param_1[iVar1 + 0xdae0a]);
LAB_0015e9b0:
          iVar2 = DebugLevel;
          if ((-1 < DebugLevel) &&
             (printk("ApCfg.ACSCheckTime[%u] = %u\n",iVar1,param_1[iVar1 + 0xdae12]),
             iVar2 = DebugLevel, -1 < DebugLevel)) {
            printk("MBSSID.wdev.bSupportMWDS = ");
            iVar2 = DebugLevel;
          }
        }
      }
      else {
        printk("ApCfg.ApCliAutoBWBTSupport = %d\n",(char)param_1[0xd9e3f]);
        iVar2 = DebugLevel;
        if (-1 < DebugLevel) {
          printk("ApCfg.bMACRepeaterEn = %d\n",*(undefined1 *)((int)param_1 + 0x36790d));
LAB_0015e90c:
          if (DebugLevel < 0) goto LAB_0015e9b0;
          printk("ApCfg.IsolateInterStaTrafficBTNBSSID = %lu\n",param_1[0xd9e3d]);
          iVar2 = DebugLevel;
          if (-1 < DebugLevel) {
            printk("ApCfg.DtimPeriod = %u\n",(char)param_1[0xdae28]);
            goto LAB_0015e95c;
          }
        }
      }
    }
    else {
      printk("bhSsid = %s\n",param_1 + 0x29f301);
      iVar2 = DebugLevel;
      if (-1 < DebugLevel) {
        printk("IndicateMediaState = %d\n",param_1[0x1e52b9]);
        if (DebugLevel < 0) goto LAB_0015e90c;
        printk("ucBFBackOffMode = %d\n",(char)param_1[0xa1657]);
        iVar2 = DebugLevel;
        if (-1 < DebugLevel) {
          printk("ApCfg.EntryClientCount = %d\n",*(undefined1 *)((int)param_1 + 0x36b916));
          goto LAB_0015e8c4;
        }
      }
    }
  }
  puVar3 = (undefined1 *)((int)param_1 + 0x2bb1a1);
  do {
    if (-1 < iVar2) {
      printk(&_LC245,*puVar3);
      iVar2 = DebugLevel;
    }
    puVar3 = puVar3 + 0x5834;
  } while (puVar3 != (undefined1 *)((int)param_1 + 0x2d6aa5));
  if ((-1 < iVar2) && (printk(&_LC45), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("MBSSID.wdev.bWmmCapable = ");
    iVar2 = DebugLevel;
  }
  piVar4 = param_1 + 0xadec7;
  do {
    if (-1 < iVar2) {
      printk(&_LC247,(char)*piVar4);
      iVar2 = DebugLevel;
    }
    piVar4 = piVar4 + 0x160d;
  } while (piVar4 != param_1 + 0xb4d08);
  if ((-1 < iVar2) && (printk(&_LC45), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("MBSSID.IsolateInterStaTraffic = ");
    iVar2 = DebugLevel;
  }
  piVar4 = param_1 + 0xaed9b;
  do {
    if (-1 < iVar2) {
      printk("%lu  ",*piVar4);
      iVar2 = DebugLevel;
    }
    piVar4 = piVar4 + 0x160d;
  } while (piVar4 != param_1 + 0xb5bdc);
  if ((-1 < iVar2) && (printk(&_LC45), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("MBSSID.IsolateInterStaMBCast = ");
    iVar2 = DebugLevel;
  }
  piVar4 = param_1 + 0xaed9c;
  do {
    if (-1 < iVar2) {
      printk(&_LC247,(char)*piVar4);
      iVar2 = DebugLevel;
    }
    piVar4 = piVar4 + 0x160d;
  } while (piVar4 != param_1 + 0xb5bdd);
  if ((-1 < iVar2) && (printk(&_LC45), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("MBSSID.MaxStaNum = ");
    iVar2 = DebugLevel;
  }
  puVar3 = (undefined1 *)((int)param_1 + 0x2bb2d6);
  do {
    if (-1 < iVar2) {
      printk(&_LC247,*puVar3);
      iVar2 = DebugLevel;
    }
    puVar3 = puVar3 + 0x5834;
  } while (puVar3 != (undefined1 *)((int)param_1 + 0x2d6bda));
  if ((-1 < iVar2) && (printk(&_LC45), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("MBSSID.bHideSsid = ");
    iVar2 = DebugLevel;
  }
  puVar3 = (undefined1 *)((int)param_1 + 0x2bb2d2);
  do {
    if (-1 < iVar2) {
      printk(&_LC247,*puVar3);
      iVar2 = DebugLevel;
    }
    puVar3 = puVar3 + 0x5834;
  } while (puVar3 != (undefined1 *)((int)param_1 + 0x2d6bd6));
  if ((-1 < iVar2) && (printk(&_LC45), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("MBSSID.AssocReqRssiThreshold = ");
    iVar2 = DebugLevel;
  }
  piVar4 = param_1 + 0xaefa1;
  do {
    if (-1 < iVar2) {
      printk(&_LC247,(int)(char)*piVar4);
      iVar2 = DebugLevel;
    }
    piVar4 = piVar4 + 0x160d;
  } while (piVar4 != param_1 + 0xb5de2);
  if ((-1 < iVar2) && (printk(&_LC45), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("MBSSID.RssiLowForStaKickOut = ");
    iVar2 = DebugLevel;
  }
  pcVar5 = (char *)((int)param_1 + 0x2bbe85);
  do {
    if (-1 < iVar2) {
      printk(&_LC247,(int)*pcVar5);
      iVar2 = DebugLevel;
    }
    pcVar5 = pcVar5 + 0x5834;
  } while (pcVar5 != (char *)((int)param_1 + 0x2d7789));
  if ((-1 < iVar2) && (printk(&_LC45), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("MBSSID.AccessControlList.Policy = ");
    iVar2 = DebugLevel;
  }
  iVar6 = 0;
  do {
    if (-1 < iVar2) {
      printk(&_LC245,*(undefined4 *)((int)param_1 + iVar6 * 0x5834 + 0x2bb671));
      iVar2 = DebugLevel;
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 != 5);
  if ((-1 < iVar2) && (printk(&_LC45), iVar2 = DebugLevel, -1 < DebugLevel)) {
    printk("MBSSID.AccessControlList.Num = ");
    iVar2 = DebugLevel;
  }
  iVar6 = 0;
  do {
    if (-1 < iVar2) {
      printk(&_LC245,*(undefined4 *)((int)param_1 + iVar6 * 0x5834 + 0x2bb675));
      iVar2 = DebugLevel;
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 != 5);
  if (iVar2 < 0) {
    return 1;
  }
  printk(&_LC45);
  if (DebugLevel < 0) {
LAB_0015e5c8:
    if (-1 < DebugLevel) {
      printk("CommonCfg.bNonVhtDisallow = %d\n",(char)param_1[0x1e565b]);
      if (DebugLevel < 0) {
        return 1;
      }
      printk("CommonCfg.TxPreamble = %lu\n",param_1[0x1e5419]);
      goto LAB_0015e610;
    }
LAB_0015e664:
    if (DebugLevel < 0) goto LAB_0015e6f8;
    printk("CommonCfg.bExtChannelSwitchAnnouncement = %d\n",(char)param_1[0x1e5652]);
    if (DebugLevel < 0) {
      return 1;
    }
    printk("CommonCfg...HTMODE = %d\n",*(byte *)((int)param_1 + 0x794cce) & 1);
  }
  else {
    printk("CommonCfg.bIEEE80211H = %d\n",(char)param_1[0x1e541d]);
    if (DebugLevel < 0) {
      return 1;
    }
    printk("CommonCfg.BeaconPeriod = %d\n",(short)param_1[0x1e5314]);
    if (-1 < DebugLevel) {
      printk("CommonCfg.MUTxRxEnable = %ld\n",param_1[0x1e5668]);
      if (DebugLevel < 0) {
        return 1;
      }
      printk("CommonCfg.bEnableTxBurst = %d\n",*(undefined1 *)((int)param_1 + 0x795071));
      goto LAB_0015e5c8;
    }
LAB_0015e610:
    if (-1 < DebugLevel) {
      printk("CommonCfg.bBssCoexEnable = %d\n",*(undefined1 *)((int)param_1 + 0x79564e));
      if (DebugLevel < 0) {
        return 1;
      }
      printk("CommonCfg.ucEDCCACtrl[%d] = %d\n",iVar1,
             *(undefined1 *)((int)param_1 + iVar1 + 0x79503b));
      goto LAB_0015e664;
    }
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("CommonCfg..bDfsEnable = %d\n",*(undefined1 *)((int)param_1 + 0x7953ef));
  if (DebugLevel < 0) {
    return 1;
  }
  printk("CommonCfg...AutoBA = %u\n",((uint)*(byte *)((int)param_1 + 0x795046) << 0x1b) >> 0x1f);
LAB_0015e6f8:
  if ((-1 < DebugLevel) &&
     (printk("CommonCfg...Policy = %u\n",((uint)*(byte *)((int)param_1 + 0x795046) << 0x19) >> 0x1e)
     , -1 < DebugLevel)) {
    printk("kickout msg fail = %u\n",param_1[0x2a1b17]);
  }
  return 1;
}

