// module: mt7915.ko
// function: Set_NetworkType_Proc @ 0x5810c
// size: 1348 bytes
//

undefined4 Set_NetworkType_Proc(int *param_1,char *param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined *puVar7;
  undefined *puVar8;
  
  iVar6 = *(int *)(*param_1 + 0x3c);
  iVar3 = iVar6 * 0x2137b0;
  puVar7 = (undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar3));
  iVar2 = strcmp(param_2,"Adhoc");
  if (iVar2 == 0) {
    if ((char)param_1[iVar6 * 0x84dec + 0xdc6ee] != '\0') {
      *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0x15fff0) = 1;
      if ((char)param_1[0xa6e43] == '\x01') {
        param_1[iVar6 * 0x84dec + 0x15ffef] = param_1[iVar6 * 0x84dec + 0x15ffef] & 0xffffff7f;
        *(undefined1 *)((int)param_1 + iVar3 + 0x580cc9) = 1;
        LinkDown(param_1,0,puVar7,0);
      }
      if ((param_1[iVar6 * 0x84dec + 0x15ffef] & 1U) != 0) {
        *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0xdc72e) = 0x20;
        __memzero(param_1 + iVar6 * 0x84dec + 0xdc726);
        LinkDown(param_1,0,puVar7,0);
        if (2 < DebugLevel) {
          printk("NDIS_STATUS_MEDIA_DISCONNECT Event BB!\n");
        }
      }
      SetCommonHtVht(param_1,puVar7);
    }
    iVar3 = DebugLevel;
    *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0xdc6ee) = 0;
    *(short *)(param_1[1] + 0x150) = (short)param_1[iVar6 * 0x84dec + 0x15ffd7];
    if (2 < iVar3) {
      printk("===>Set_NetworkType_Proc::(AD-HOC)\n");
    }
  }
  else {
    iVar2 = strcmp(param_2,"Infra");
    if (iVar2 == 0) {
      if ((char)param_1[iVar6 * 0x84dec + 0xdc6ee] != '\x01') {
        *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0x15fff0) = 1;
        if ((char)param_1[0xa6e43] == '\x01') {
          param_1[iVar6 * 0x84dec + 0x15ffef] = param_1[iVar6 * 0x84dec + 0x15ffef] & 0xffffff7f;
          *(undefined1 *)((int)param_1 + iVar3 + 0x580cc9) = 1;
          LinkDown(param_1,0,puVar7,0);
          *(undefined1 *)(param_1 + 0xa6e43) = 0;
        }
        if ((param_1[0x1e5449] & 2U) != 0) {
          *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0xdc72e) = 0x20;
          __memzero(param_1 + iVar6 * 0x84dec + 0xdc726,0x20);
          LinkDown(param_1,0,puVar7,0);
        }
        SetCommonHtVht(param_1,puVar7);
      }
      iVar3 = DebugLevel;
      *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0xdc6ee) = 1;
      *(short *)(param_1[1] + 0x150) = (short)param_1[iVar6 * 0x84dec + 0x15ffd7];
      if (2 < iVar3) {
        printk("===>Set_NetworkType_Proc::(INFRA)\n");
      }
    }
    else {
      iVar2 = strcmp(param_2,"Monitor");
      if (iVar2 == 0) {
        uVar5 = param_1[iVar6 * 0x84dec + 0x15ffef];
        param_1[0x1e5449] = param_1[0x1e5449] & 0xfffffffd;
        param_1[iVar6 * 0x84dec + 0x15ffef] = uVar5 & 0xfffffffe | 0x80;
        *(undefined1 *)((int)param_1 + iVar3 + 0x580cc9) = 0;
        MlmeRestartStateMachine(param_1,puVar7);
        if (2 < DebugLevel) {
          printk("fSTA_STATUS_MEDIA_STATE_CONNECTED\n");
        }
        wlan_operate_set_prim_ch(puVar7,*(undefined1 *)((int)param_1 + iVar6 * 0x2137b0 + 0x36db72))
        ;
        if (DebugLevel < 3) {
          *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0xdc6ee) = 3;
          *(undefined1 *)(param_1 + 0xa6e43) = 1;
          *(undefined2 *)(param_1[1] + 0x150) = 0x322;
        }
        else {
          iVar3 = wlan_operate_get_bw(puVar7);
          uVar1 = *(undefined1 *)((int)param_1 + iVar6 * 0x2137b0 + 0x36db72);
          puVar8 = &_LC16;
          if (iVar3 == 1) {
            puVar8 = &_LC15;
          }
          uVar4 = wlan_operate_get_cen_ch_1(puVar7);
          printk("%s():BW_%s, CtrlChannel(%d), CentralChannel(%d)\n","Set_NetworkType_Proc",puVar8,
                 uVar1,uVar4);
          *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0xdc6ee) = 3;
          iVar3 = DebugLevel;
          *(undefined1 *)(param_1 + 0xa6e43) = 1;
          *(undefined2 *)(param_1[1] + 0x150) = 0x322;
          if (2 < iVar3) {
            printk("===>Set_NetworkType_Proc::(MONITOR)\n");
          }
        }
      }
    }
  }
  AsicSetRxFilter(param_1);
  iVar3 = DebugLevel;
  *(undefined1 *)((int)param_1 + iVar6 * 0x2137b0 + 0x580311) = 0;
  if (2 < iVar3) {
    printk("Set_NetworkType_Proc::(NetworkType=%d)\n",(char)param_1[iVar6 * 0x84dec + 0xdc6ee]);
  }
  return 1;
}

