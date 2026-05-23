// module: mt7915.ko
// function: Set_WscGetConf_Proc @ 0x59354
// size: 2180 bytes
//

undefined4 Set_WscGetConf_Proc(int *param_1)

{
  bool bVar1;
  int *piVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  uint uVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  char *local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  char *local_68;
  char *local_64;
  char *local_5c;
  int local_58;
  int *local_54;
  int *local_50;
  uint local_4c;
  undefined1 auStack_48 [12];
  char *local_3c [3];
  undefined4 ****local_30;
  undefined4 ****local_2c;
  
  iVar11 = DebugLevel;
  iVar9 = *(int *)(*param_1 + 0x3c);
  local_58 = iVar9 * 0x20;
  iVar5 = iVar9 * 0x2137b0;
  if (param_1[iVar9 * 0x84dec + 0xdbb8f] == 0) {
    *(undefined1 *)(param_1 + iVar9 * 0x84dec + 0xdc608) = 0;
    uVar4 = 0;
    if (2 < iVar11) {
      printk("Set_WscGetConf_Proc: WPS is disabled.\n");
    }
  }
  else {
    piVar10 = param_1 + iVar9 * 0x84dec + 0xdbb8f;
    _WscStop(param_1,0,piVar10,0);
    *(undefined1 *)(param_1 + iVar9 * 0x84dec + 0xdbc95) = 1;
    param_1[iVar9 * 0x84dec + 0xdbb93] = 1;
    iVar11 = DebugLevel;
    uVar8 = param_1[iVar9 * 0x84dec + 0x15ffef] & 1;
    if (uVar8 == 0) {
      local_54 = param_1 + 0x1e4000;
      if ((param_1[0x1e5449] & 2U) == 0) {
        local_50 = &DebugLevel;
      }
      else {
        *(undefined1 *)(param_1 + iVar9 * 0x84dec + 0xdc72e) = 0x20;
        __memzero(param_1 + iVar9 * 0x84dec + 0xdc726);
        if (param_1[iVar9 * 0x84dec + 0xdbb90] == 1) {
          local_5c = (char *)0x0;
        }
        else {
          local_5c = (char *)0x4;
        }
        local_50 = (int *)0x2;
        AsicDisableSync(param_1,0);
        local_78 = (char *)(uint)*(ushort *)((int)param_1 + iVar5 + 0x36ee46);
        local_68 = (char *)local_50;
        local_74 = uVar8;
        local_70 = uVar8;
        local_6c = uVar8;
        WscBuildBeaconIE(param_1,(char)param_1[iVar9 * 0x84dec + 0xdbb91],1,local_5c);
        piVar2 = local_50;
        local_78 = local_5c;
        local_68 = (char *)uVar8;
        if (param_1[iVar9 * 0x84dec + 0xdbb8f] == 4) {
          local_5c = (char *)local_50;
          local_74 = (uint)*(ushort *)((int)param_1 + iVar5 + 0x36ee46);
          local_64 = (char *)local_50;
          local_50 = &DebugLevel;
          local_70 = uVar8;
          local_6c = uVar8;
          WscBuildProbeRespIE(param_1,piVar2,(char)param_1[iVar9 * 0x84dec + 0xdbb91],1);
          UpdateBeaconHandler(param_1,(undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar5)),1);
          AsicEnableIbssSync(param_1,(short)local_54[0x1314],0,local_5c);
        }
        else {
          local_74 = (uint)*(ushort *)((int)param_1 + iVar5 + 0x36ee46);
          local_64 = (char *)local_50;
          local_50 = &DebugLevel;
          local_70 = uVar8;
          local_6c = uVar8;
          WscBuildProbeRespIE(param_1,0,(char)param_1[iVar9 * 0x84dec + 0xdbb91],1);
          LinkDown(param_1,0,(undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar5)),0);
        }
      }
    }
    else {
      local_50 = &DebugLevel;
      *(undefined1 *)(param_1 + iVar9 * 0x84dec + 0x15fe68) = 1;
      if (2 < iVar11) {
        printk("disassociate with current AP before starting WPS\n");
      }
      iVar5 = local_58 * 4 + iVar9 * 5;
      local_78 = "Set_WscGetConf_Proc";
      local_74 = 0x7c7;
      __cntl_disconnect_request
                ((undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar5 * 0x3ff0)),1,
                 (undefined *)((int)param_1 + (int)(&DAT_0057ff80 + iVar5 * 0x3ff0)),8);
      *(undefined1 *)(param_1 + iVar5 * 0xffc + 0xdc72e) = 0x20;
      __memzero(param_1 + iVar5 * 0xffc + 0xdc726);
      *(undefined1 *)(param_1 + iVar5 * 0xffc + 0xdc608) = 0;
      if ((*(uint *)(((uint)&local_78 & 0xffffe000) + 4) & 0x1fff00) == 0) {
        __init_waitqueue_head(auStack_48,"&_wait",&_LANCHOR1);
        iVar5 = 0x32;
        local_5c = (char *)0x0;
        do {
          local_3c[0] = local_5c;
          local_30 = &local_30;
          local_2c = &local_30;
          for (iVar11 = 1; iVar6 = prepare_to_wait_event(auStack_48,local_3c,1),
              iVar11 != 0 && iVar6 == 0; iVar11 = schedule_timeout(iVar11)) {
          }
          finish_wait(auStack_48,local_3c);
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      else {
        RtmpusecDelay(500000);
      }
    }
    iVar5 = local_58 * 4 + iVar9 * 5;
    *(undefined1 *)(param_1 + iVar5 * 0xffc + 0xdc608) = 1;
    *(undefined1 *)(param_1 + iVar5 * 0xffc + 0xdbb91) = 1;
    if (param_1[iVar5 * 0xffc + 0xdbb90] == 1) {
      if (((char)param_1[iVar5 * 0xffc + 0xdc6ee] == '\x01') &&
         (param_1[iVar5 * 0xffc + 0xdbb8f] == 1)) {
        *(undefined1 *)((int)param_1 + iVar5 * 0x3ff0 + 0x36ee9f) = 0;
        *(undefined1 *)(param_1 + iVar5 * 0xffc + 0xdbbaa) = 0;
        WscPINAction(param_1,piVar10);
        bVar1 = true;
      }
      else {
        local_5c = (char *)0xc9;
        WscInitRegistrarPair(param_1,piVar10,0);
        iVar5 = (local_58 * 4 + iVar9 * 5) * 0x3ff0;
        local_54 = (int *)((int)param_1 + (int)(&DAT_0036db58 + iVar5));
        *(undefined1 *)((int)param_1 + iVar5 + 0x580ccd) = 1;
        local_4c = (uint)&local_78 & 0xffffe000;
        while ((iVar5 = scan_in_run_state(param_1,local_54), iVar5 == 1 &&
               (local_5c = local_5c + -1, local_5c != (char *)0x0))) {
          if ((*(uint *)(local_4c + 4) & 0x1fff00) == 0) {
            __init_waitqueue_head(auStack_48,"&_wait",&_LANCHOR1);
            iVar5 = 0x32;
            do {
              local_3c[0] = (char *)0x0;
              local_30 = &local_30;
              local_2c = &local_30;
              for (iVar11 = 1; iVar6 = prepare_to_wait_event(auStack_48,local_3c,1),
                  iVar11 != 0 && iVar6 == 0; iVar11 = schedule_timeout(iVar11)) {
              }
              finish_wait(auStack_48,local_3c);
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
          }
          else {
            RtmpusecDelay(500000);
          }
        }
        bVar1 = true;
        iVar5 = local_58 * 4 + iVar9 * 5;
        *(undefined1 *)(param_1 + iVar5 * 0xffc + 0xdc72e) = 0;
        *(undefined1 *)(param_1 + iVar5 * 0xffc + 0x15fff0) = 1;
        cntl_connect_request(local_54,1,6,(int)param_1 + iVar5 * 0x3ff0 + 0x36ee89);
        param_1[iVar5 * 0xffc + 0xdbb93] = 2;
        RTMPSetTimer(param_1 + iVar5 * 0xffc + 0xdc2a6,120000);
        *(undefined1 *)((int)param_1 + iVar5 * 0x3ff0 + 0x370a97) = 1;
        param_1[iVar5 * 0xffc + 0xdbb92] = 3;
      }
    }
    else if (((char)param_1[iVar5 * 0xffc + 0xdc6ee] == '\x01') ||
            (param_1[iVar5 * 0xffc + 0xdbb8f] == 1)) {
      iVar5 = local_58 * 4 + iVar9 * 5;
      bVar1 = true;
      param_1[iVar5 * 0xffc + 0xdbb99] = 0;
      __memzero(param_1 + iVar5 * 0xffc + 0xdbb99,0x24);
      RTMPZeroMemory((int)param_1 + iVar5 * 0x3ff0 + 0x36ee89,6);
      *(undefined1 *)(param_1 + iVar5 * 0xffc + 0xdbba2) = 0;
      WscPushPBCAction(param_1,piVar10);
    }
    else {
      WscInitRegistrarPair(param_1,piVar10,0);
      WscGetRegDataPIN(param_1,param_1[iVar5 * 0xffc + 0xdbb94],piVar10);
      bVar1 = false;
      RTMPSetTimer(param_1 + iVar5 * 0xffc + 0xdc2a6,120000);
      *(undefined1 *)((int)param_1 + iVar5 * 0x3ff0 + 0x370a97) = 1;
      param_1[iVar5 * 0xffc + 0xdbb93] = 5;
    }
    iVar5 = local_58 * 4 + iVar9 * 5;
    iVar11 = iVar5 * 0x3ff0;
    puVar7 = (undefined1 *)((int)param_1 + iVar11 + 0x36f193);
    uVar4 = HcGetBandByWdev(param_1[iVar5 * 0xffc + 0xdc60a]);
    RTMPSetLED(param_1,8,uVar4);
    do {
      uVar3 = RandomByte(param_1);
      puVar7 = puVar7 + 1;
      *puVar7 = uVar3;
    } while (puVar7 != (undefined1 *)((int)param_1 + iVar11 + 0x36f253));
    iVar5 = local_58 * 4 + iVar9 * 5;
    if ((char)param_1[iVar5 * 0xffc + 0xdc5ac] != '\0') {
      *(undefined1 *)(param_1 + iVar5 * 0xffc + 0xdc5ac) = 0;
      RTMPCancelTimer(param_1 + iVar5 * 0xffc + 0xdc5ad,local_3c);
    }
    if (bVar1) {
      RtmpOsMlmeUp(param_1 + 0xa18a6);
    }
    if (*local_50 < 3) {
      uVar4 = 1;
    }
    else {
      uVar4 = 1;
      printk("Set_WscGetConf_Proc trigger WSC state machine\n");
    }
  }
  return uVar4;
}

