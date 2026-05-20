// module: mt7915.ko
// function: RTMPIoctlShow @ 0x61748
// size: 2080 bytes
//

void RTMPIoctlShow(int *param_1,int param_2,undefined4 param_3,undefined4 *param_4)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  undefined4 uVar4;
  uint uVar5;
  char *__format;
  int iVar6;
  char *__s;
  int *piVar7;
  uint uVar8;
  char *local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  size_t local_34;
  int local_2c [2];
  
  __s = (char *)*param_4;
  local_34 = param_4[1];
  iVar6 = *(int *)(*param_1 + 0x3c);
  piVar7 = param_1 + iVar6 * 0x84dec + 0xdb6d6;
  os_alloc_mem(0,local_2c,*(undefined2 *)(param_2 + 0x14));
  if (local_2c[0] == 0) {
    return;
  }
  uVar5 = (uint)*(ushort *)(param_2 + 0x14);
  uVar8 = *(uint *)(((uint)&local_50 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar5) && *(uint *)(param_2 + 0x10) + uVar5 <= uVar8) {
    uVar8 = 0;
  }
  if (uVar8 == 0) {
    iVar2 = __copy_from_user();
    if (iVar2 != 0) goto LAB_000618fc;
  }
  else if (uVar5 != 0) {
    __memzero(local_2c[0],uVar5);
LAB_000618fc:
    if (-1 < DebugLevel) {
      printk("%s(): copy from user failed\n","RTMPIoctlShow");
    }
  }
  switch(param_3) {
  case 1:
    getIPMacTbInfo(param_1 + 0x1e52ca,__s,local_34);
    sVar3 = strlen(__s);
    *(short *)(param_2 + 0x14) = (short)sVar3 + 1;
    break;
  case 2:
    getIPv6MacTbInfo(param_1 + 0x1e52ca,__s,local_34);
    sVar3 = strlen(__s);
    *(short *)(param_2 + 0x14) = (short)sVar3 + 1;
    break;
  case 3:
    local_44 = (uint)*(byte *)((int)param_1 + 0xa77bcd);
    local_40 = (uint)*(byte *)((int)param_1 + 0xa77bce);
    local_50 = (char *)(uint)*(byte *)((int)param_1 + 0xa77bca);
    local_4c = (uint)*(byte *)((int)param_1 + 0xa77bcb);
    local_48 = (uint)*(byte *)(param_1 + 0x29def3);
    snprintf(__s,local_34,"%02x:%02x:%02x:%02x:%02x:%02x\n",(uint)*(byte *)((int)param_1 + 0xa77bc9)
            );
    sVar3 = strlen(__s);
    *(short *)(param_2 + 0x14) = (short)sVar3 + 1;
    break;
  case 4:
    if ((char)param_1[0xa6e43] == '\x01') {
      if (((*(ushort *)(param_1 + iVar6 * 0x84dec + 0xdb6dc) & 0x18) == 0) ||
         (iVar2 = wlan_operate_get_ht_bw(piVar7), iVar2 == 0)) {
        snprintf(__s,local_34,"Monitor Mode(Channel %d)\n",
                 (uint)*(byte *)((int)param_1 + iVar6 * 0x2137b0 + 0x36db72));
      }
      else {
        uVar4 = wlan_operate_get_cen_ch_1(piVar7);
        snprintf(__s,local_34,"Monitor Mode(CentralChannel %d)\n",uVar4);
      }
    }
    else if (param_1[0x1e52b9] == 1) {
      if ((param_1[iVar6 * 0x84dec + 0x15ffef] & 1U) == 0) {
        if ((param_1[0x1e5449] & 2U) != 0) {
          snprintf(__s,local_34,"Connected\n");
        }
      }
      else {
        local_50 = (char *)(uint)*(byte *)(param_1 + iVar6 * 0x84dec + 0x15ffe0);
        local_4c = (uint)*(byte *)((int)param_1 + iVar6 * 0x2137b0 + 0x57ff81);
        iVar2 = (int)param_1 + iVar6 * 0x2137b0 + 0x57ff5e;
        local_48 = (uint)*(byte *)((int)param_1 + iVar6 * 0x2137b0 + 0x57ff82);
        local_44 = (uint)*(byte *)((int)param_1 + iVar6 * 0x2137b0 + 0x57ff83);
        local_40 = (uint)*(byte *)(param_1 + iVar6 * 0x84dec + 0x15ffe1);
        local_3c = (uint)*(byte *)((int)param_1 + iVar6 * 0x2137b0 + 0x57ff85);
        snprintf(__s,local_34,"Connected(AP: %s[%02x:%02x:%02x:%02x:%02x:%02x])\n",iVar2);
        if (2 < DebugLevel) {
          printk("Ssid=%s ,Ssidlen = %d\n",iVar2,
                 *(undefined1 *)((int)param_1 + iVar6 * 0x2137b0 + 0x57ff7e));
        }
      }
    }
    else {
      snprintf(__s,local_34,"Disconnected\n");
      if (2 < DebugLevel) {
        printk("ConnStatus is not connected\n");
      }
    }
    goto LAB_00061a34;
  case 5:
    snprintf(__s,local_34,"Driver version-%s\n",&_LC179);
    goto LAB_00061a34;
  case 6:
    getBaInfo(param_1,__s,local_34);
    sVar3 = strlen(__s);
    *(short *)(param_2 + 0x14) = (short)sVar3 + 1;
    break;
  case 7:
    Show_DescInfo_Proc(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  default:
    if (2 < DebugLevel) {
      printk("%s - unknow subcmd = %d\n","RTMPIoctlShow",param_3);
    }
    break;
  case 10:
    if (((param_1[0x28e7e1] & 0x100U) == 0) &&
       (((param_1[iVar6 * 0x84dec + 0x15ffef] & 1U) != 0 || ((param_1[0x1e5449] & 2U) != 0)))) {
      local_4c = 0x1945;
      local_50 = "RTMPIoctlShow";
      __cntl_disconnect_request(piVar7,1,param_1 + iVar6 * 0x84dec + 0x15ffe0,8);
      RtmpusecDelay(1000);
    }
    MlmeRestartStateMachine(param_1,piVar7);
    cVar1 = *(char *)((int)param_1 + iVar6 * 0x2137b0 + 0x580c92);
    *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0x160324) = 0;
    if (cVar1 != '\0') {
      *(undefined1 *)((int)param_1 + iVar6 * 0x2137b0 + 0x580c92) = 0;
      MlmeRadioOff(param_1,piVar7);
      param_1[0x28e7e9] = 3;
    }
    __format = "Radio Off\n";
    goto LAB_00061a9c;
  case 0xb:
    cVar1 = *(char *)((int)param_1 + iVar6 * 0x2137b0 + 0x580c91);
    *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0x160324) = 1;
    if (cVar1 == '\0') {
      *(undefined1 *)((int)param_1 + iVar6 * 0x2137b0 + 0x580c92) = 0;
    }
    else {
      *(undefined1 *)((int)param_1 + iVar6 * 0x2137b0 + 0x580c92) = 1;
      MlmeRadioOn(param_1,piVar7);
      param_1[0x28e7e9] = -1;
    }
    __format = "Radio On\n";
LAB_00061a9c:
    snprintf(__s,local_34,__format);
    goto LAB_00061a34;
  case 0x15:
    iVar6 = RTMPShowCfgValue(param_1,local_2c[0],__s,param_4[1]);
    if (iVar6 != 0) break;
LAB_00061a34:
    sVar3 = strlen(__s);
    *(short *)(param_2 + 0x14) = (short)sVar3 + 1;
    break;
  case 0x16:
    Show_Adhoc_MacTable_Proc(param_1,__s,local_34);
    sVar3 = strlen(__s);
    *(short *)(param_2 + 0x14) = (short)sVar3 + 1;
    break;
  case 0x1a:
    show_devinfo_proc(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x1b:
    Show_MacTable_Proc(param_1,&_LC271);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x1c:
    show_trinfo_proc(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x1d:
    show_sysinfo_proc(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x1e:
    chip_show_pwr_info(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x20:
    show_wtbl_proc(param_1,local_2c[0]);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x21:
    show_mib_proc(param_1,local_2c[0]);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x23:
    ShowTmacInfo(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x24:
    ShowAggInfo(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x25:
    ShowPseInfo(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x26:
    ShowPseData(param_1,local_2c[0]);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x27:
    show_dmasch_proc(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x29:
    ShowDbdcProc(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x2a:
    show_wtbltlv_proc(param_1,local_2c[0]);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x2d:
    ShowWifiInterruptCntProc(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x2e:
    show_efuseinfo_proc(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x2f:
    ShowPLEInfo(param_1,local_2c[0]);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x31:
    show_tx_burst_info(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x32:
    show_TXD_proc(param_1,local_2c[0]);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x33:
    show_mem_proc(param_1,local_2c[0]);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x34:
    show_e2pinfo_proc(param_1,0);
  case 0x1f:
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x35:
    show_tpinfo_proc(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
    break;
  case 0x36:
    ShowChCtrl(param_1,0);
    *(undefined2 *)(param_2 + 0x14) = 0;
  }
  os_free_mem(local_2c[0]);
  return;
}

