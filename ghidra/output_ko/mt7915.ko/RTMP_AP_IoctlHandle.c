// module: mt7915.ko
// function: RTMP_AP_IoctlHandle @ 0x3f348
// size: 1692 bytes
//

uint RTMP_AP_IoctlHandle(int *param_1,int param_2,undefined4 param_3,uint param_4,int *param_5,
                        uint param_6)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  
  iVar9 = *param_1;
  switch(param_3) {
  case 1:
    RTMPIoctlSetWSCOOB();
    uVar6 = 0;
    break;
  case 2:
    RTMPIoctlGetMacTable();
    uVar6 = 0;
    break;
  case 3:
    RTMPIoctlGetSiteSurvey();
    uVar6 = 0;
    break;
  case 4:
    RTMPAPPrivIoctlGetConnectStatus();
    uVar6 = 0;
    break;
  case 5:
    RTMPIoctlStatistics();
    uVar6 = 0;
    break;
  case 6:
    RTMPIoctlRvRDebug();
    uVar6 = 0;
    break;
  case 7:
    uVar6 = RTMPIoctlRXStatistics();
    return uVar6;
  case 8:
    RTMPIoctlQueryBaTable();
    uVar6 = 0;
    break;
  case 9:
    RTMPAPIoctlE2PROM();
    uVar6 = 0;
    break;
  case 10:
    if (2 < DebugLevel) {
      printk("IOCTL::(iwpriv) Command not Support!\n");
      return 0;
    }
  case 0xc:
switchD_0003f368_caseD_c:
    uVar6 = 0;
    break;
  case 0xb:
    RTMPIoctlMAC();
    uVar6 = 0;
    break;
  case 0xd:
    if ((param_4 & 0x8000) == 0) {
      uVar6 = RTMPAPQueryInformation();
      return uVar6;
    }
    uVar6 = RTMPAPSetInformation(param_1,param_2,param_4);
    return uVar6;
  case 0xe:
    uVar6 = RTMPAPPrivIoctlSet();
    return uVar6;
  case 0xf:
    uVar6 = RTMPAPPrivIoctlShow();
    return uVar6;
  default:
    uVar6 = RTMP_COM_IoctlHandle();
    return uVar6;
  case 0x13:
    RTMPIoctlGetMacTableStaInfo();
    uVar6 = 0;
    break;
  case 0x14:
    uVar5 = get_default_wdev();
    UpdateBeaconHandler(param_1,uVar5,4);
    uVar6 = 0;
    break;
  case 0x17:
    if (2 < DebugLevel) {
      printk("%s -> CMD_RTPRIV_IOCTL_MBSS_INIT\n","RTMP_AP_IoctlHandle");
    }
    MBSS_Init(param_1,param_5);
    uVar6 = 0;
    break;
  case 0x18:
    if (2 < DebugLevel) {
      printk("%s -> CMD_RTPRIV_IOCTL_MBSS_REMOVE\n","RTMP_AP_IoctlHandle");
    }
    MBSS_Remove(param_1);
    uVar6 = 0;
    break;
  case 0x19:
    iVar9 = ext_mbss_hw_cr_enable(param_5);
    uVar6 = (uint)(iVar9 != 0);
    break;
  case 0x1a:
    iVar9 = ext_mbss_hw_cr_disable(param_5);
    uVar6 = (uint)(iVar9 != 0);
    break;
  case 0x1b:
    RTMPIoctlWscProfile();
    uVar6 = 0;
    break;
  case 0x1c:
    WscGenerateUUID(param_1,param_5 + 0xf42,param_5 + 0xf46,0,0,1);
    *(undefined1 *)((int)param_5 + 0x3ec5) = 0;
    *(undefined2 *)(param_5 + 0xfb4) = 0x80;
    param_5[0xfb3] = 0;
    param_5[0xfb2] = 0;
    os_alloc_mem(param_1,param_5 + 0xfb2,0x900);
    if (param_5[0xfb2] != 0) {
      __memzero(param_5[0xfb2],0x900);
    }
    param_5[0xfb5] = 0;
    param_5[0xfb6] = 0;
    os_alloc_mem(param_1,param_5 + 0xfb6,0x900);
    if (param_5[0xfb6] != 0) {
      __memzero(param_5[0xfb6],0x900);
    }
    *(undefined1 *)(param_5 + 0xf85) = 1;
    uVar6 = 0;
    param_5[0xfbb] = 0;
    param_5[0xfba] = 0;
    *(undefined1 *)(param_5 + 0xfbc) = 0;
    param_5[0xfb9] = 0;
    *(undefined1 *)((int)param_5 + 0x3ebe) = 0;
    *(undefined1 *)((int)param_5 + 0x3ebd) = 0;
    *(undefined2 *)((int)param_5 + 0x3e0a) = 0;
    param_5[0xf83] = 0;
    *(undefined1 *)(param_5 + 0xf84) = 0;
    *(undefined1 *)((int)param_5 + 0x3e15) = 1;
    *(undefined2 *)(param_5 + 0xf82) = 0;
    WscInit(param_1,1,param_6 & 0xff);
    break;
  case 0x1d:
    ApCliIfUp();
    uVar6 = 0;
    break;
  case 0x1e:
    __cntl_disconnect_request
              ((undefined *)((int)param_1 + (int)(&DAT_0036db58 + param_6 * 0x2137b0)),1,
               (undefined *)((int)param_1 + (int)(&DAT_0057ff80 + param_6 * 0x2137b0)),8,
               "RTMP_AP_IoctlHandle",0x5030);
    uVar6 = 0;
    break;
  case 0x22:
    iVar9 = RTMP_AP_IoctlPrepare(param_1,param_5);
    param_5[8] = iVar9;
    uVar6 = (uint)(iVar9 != 0);
    break;
  case 0x23:
    iVar9 = *(int *)(iVar9 + 0x3c);
    if (param_6 == 0x400) {
      if (*(char *)((int)param_1 + iVar9 * 0x2137b0 + 0x580e8e) == '\x01') {
        param_1 = param_1 + (uint)*(ushort *)(param_1 + iVar9 * 0x84dec + 0x16038e) * 0x530 +
                            0x28783;
        goto LAB_0003f7dc;
      }
    }
    else {
      param_1 = (int *)((int)param_1 + iVar9 * 0x5834 + 0x2b7269);
LAB_0003f7dc:
      if (param_1 != (int *)0x0) {
        *param_5 = *param_1;
        iVar9 = DebugLevel;
        *(short *)(param_5 + 1) = (short)param_1[1];
        if (2 < iVar9) {
          printk("IOCTL::SIOCGIWAP(=%02x:%02x:%02x:%02x:%02x:%02x)\n",(int)(char)*param_1,
                 (int)*(char *)((int)param_1 + 1),(int)*(char *)((int)param_1 + 2),
                 (int)*(char *)((int)param_1 + 3),(int)(char)param_1[1],
                 (int)*(char *)((int)param_1 + 5));
          return 0;
        }
        goto switchD_0003f368_caseD_c;
      }
    }
    __memzero(param_5,6);
    uVar6 = 0;
    break;
  case 0x24:
    iVar8 = *(int *)(iVar9 + 0x3c);
    iVar4 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
    if (iVar8 < iVar4) {
      iVar9 = *(int *)(iVar9 + 0x3c);
      puVar7 = *(undefined4 **)(param_2 + 0x10);
      *puVar7 = *(undefined4 *)((int)param_1 + iVar9 * 0x5834 + 0x2b7269);
      *(undefined2 *)(puVar7 + 1) = *(undefined2 *)((int)param_1 + iVar9 * 0x5834 + 0x2b726d);
      return 0;
    }
    goto switchD_0003f368_caseD_c;
  case 0x25:
    if (*param_5 == 0x400) {
      if (*(char *)((int)param_1 + *(int *)(iVar9 + 0x3c) * 0x2137b0 + 0x580e8e) == '\x01') {
        uVar6 = 0;
        param_5[3] = (uint)*(byte *)((int)param_1 + *(int *)(iVar9 + 0x3c) * 0x2137b0 + 0x57ff7e);
        param_5[2] = (int)param_1 + *(int *)(iVar9 + 0x3c) * 0x2137b0 + 0x57ff5e;
      }
      else {
        uVar6 = 0;
        param_5[3] = 0;
        param_5[2] = 0;
      }
    }
    else {
      uVar6 = 0;
      bVar1 = *(byte *)((int)param_1 + param_5[1] * 0x5834 + 0x2bb2d1);
      param_5[2] = (int)((int)param_1 +
                        (int)(
                             "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                             + param_5[1] * 0x5834 + 0x34));
      param_5[3] = (uint)bVar1;
    }
    break;
  case 0x26:
    if (*param_5 == 0x400) {
      iVar9 = *(int *)(iVar9 + 0x3c);
      bVar1 = *(byte *)((int)param_1 + iVar9 * 0x2137b0 + 0x36e40b);
      bVar2 = *(byte *)((int)param_1 + iVar9 * 0x2137b0 + 0x36e40a);
      uVar3 = *(ushort *)((int)param_1 + iVar9 * 0x2137b0 + 0x36e40a);
    }
    else {
      iVar9 = *(int *)(iVar9 + 0x3c);
      bVar1 = *(byte *)((int)param_1 + iVar9 * 0x5834 + 0x2b7afb);
      bVar2 = *(byte *)((int)param_1 + iVar9 * 0x5834 + 0x2b7afa);
      uVar3 = *(ushort *)((int)param_1 + iVar9 * 0x5834 + 0x2b7afa);
    }
    RtmpDrvMaxRateGet(param_1,bVar1 >> 5,((uint)bVar1 << 0x1e) >> 0x1f,((uint)uVar3 << 0x17) >> 0x1e
                      ,bVar2 & 0x3f,*(byte *)(param_1 + 0xa5b73) >> 4,param_5 + 1);
    uVar6 = 0;
    break;
  case 0x28:
    RTMPIoctlGetDriverInfo();
    uVar6 = 0;
    break;
  case 0x29:
    RTMPIoctlWscPINCode();
    uVar6 = 0;
    break;
  case 0x2a:
    uVar6 = RTMPAPPrivIoctlGetBusyTime();
    return uVar6;
  case 0x2b:
    RTMPIoctlGetWpsRunningState();
    uVar6 = 0;
    break;
  case 0x2c:
    ZTE_Get_CurrentBandWidth();
    uVar6 = 0;
    break;
  case 0x2d:
    RTMPIoctlGetRadioStats();
    uVar6 = 0;
    break;
  case 0x2e:
    uVar6 = RTMPPhyState();
    return uVar6;
  case 0x2f:
    RTMPIoctlGetHopRun();
    uVar6 = 0;
    break;
  case 0x30:
    RTMPIoctlGetASSOCDATA();
    uVar6 = 0;
    break;
  case 0x32:
    RTMPIoctlStaStats();
    uVar6 = 0;
    break;
  case 0x33:
    ZTE_Get_Driver_Stat();
    uVar6 = 0;
  }
  return uVar6;
}

