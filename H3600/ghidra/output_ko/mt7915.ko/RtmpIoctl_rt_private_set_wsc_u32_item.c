// module: mt7915.ko
// function: RtmpIoctl_rt_private_set_wsc_u32_item @ 0x64c00
// size: 1320 bytes
//

undefined4 RtmpIoctl_rt_private_set_wsc_u32_item(int *param_1,int *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  puVar1 = (undefined4 *)*param_2;
  iVar2 = *(int *)(*param_1 + 0x3c);
  switch(*puVar1) {
  case 1:
    uVar3 = puVar1[1];
    if (2 < DebugLevel) {
      printk("%s - WSC_CREDENTIAL_COUNT, value = %d\n","RtmpIoctl_rt_private_set_wsc_u32_item",uVar3
            );
    }
    if (8 < uVar3) goto LAB_00064d68;
    param_1[iVar2 * 0x84dec + 0xdc2b3] = uVar3;
    break;
  default:
    if (2 < DebugLevel) {
      printk("%s - unknow subcmd = %d, value = %d\n","RtmpIoctl_rt_private_set_wsc_u32_item",*puVar1
             ,0);
    }
    break;
  case 8:
    uVar3 = puVar1[1];
    if (2 < DebugLevel) {
      printk("%s - WSC_SET_DRIVER_CONNECT_BY_CREDENTIAL_IDX, value = %d\n",
             "RtmpIoctl_rt_private_set_wsc_u32_item",uVar3);
    }
    if ((7 < uVar3) || ((uint)param_1[iVar2 * 0x84dec + 0xdc2b3] <= uVar3)) goto LAB_00064d68;
    WscWriteConfToPortCfg
              (param_1,param_1 + iVar2 * 0x84dec + 0xdbb8f,
               &DAT_00370ad4 + (int)(param_1 + uVar3 * 0x1d + iVar2 * 0x84dec),1);
    *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0x15fe68) = 1;
    LinkDown(param_1,1,(undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar2 * 0x2137b0)),0);
    break;
  case 9:
    uVar3 = puVar1[1];
    if (2 < DebugLevel) {
      printk("%s - WSC_SET_DRIVER_AUTO_CONNECT, value = %d\n",
             "RtmpIoctl_rt_private_set_wsc_u32_item",uVar3);
    }
    if (2 < uVar3) goto LAB_00064d68;
    *(char *)(param_1 + iVar2 * 0x84dec + 0xdc5d7) = (char)uVar3;
    break;
  case 10:
    iVar2 = puVar1[1];
    if (2 < DebugLevel) {
      printk("%s - WSC_SET_CONF_MODE, value = %d\n","RtmpIoctl_rt_private_set_wsc_u32_item",iVar2);
    }
    if (iVar2 != 2) {
      if (iVar2 == 1) {
        Set_WscConfMode_Proc(param_1,&_LC166);
        return 0;
      }
      if (iVar2 == 0) {
        Set_WscConfMode_Proc(param_1,&_LC168);
        return 0;
      }
      if (iVar2 != 4) goto LAB_00064d68;
    }
    Set_WscConfMode_Proc(param_1,&_LC167);
    break;
  case 0xb:
    iVar2 = puVar1[1];
    if (2 < DebugLevel) {
      printk("%s - WSC_SET_MODE, value = %d\n","RtmpIoctl_rt_private_set_wsc_u32_item",iVar2);
    }
    if (iVar2 == 2) {
      iVar2 = Set_WscMode_Proc(param_1,&_LC167);
    }
    else {
      if (iVar2 == 3) {
        iVar2 = Set_WscMode_Proc(param_1,&_LC170);
        if (iVar2 != 0) {
          return 0;
        }
        goto LAB_00064d68;
      }
      if (iVar2 != 1) goto LAB_00064d68;
      iVar2 = Set_WscMode_Proc(param_1,&_LC166);
    }
    if (iVar2 == 0) {
LAB_00064d68:
      param_2[1] = 30000;
      return 0;
    }
    break;
  case 0xe:
    if (2 < DebugLevel) {
      printk("%s - WSC_START\n","RtmpIoctl_rt_private_set_wsc_u32_item");
    }
    Set_WscGetConf_Proc(param_1,&_LC166);
    return 0;
  case 0xf:
    if (2 < DebugLevel) {
      printk("%s - WSC_STOP\n","RtmpIoctl_rt_private_set_wsc_u32_item");
    }
    if ((((param_1[iVar2 * 0x84dec + 0x15ffef] & 1U) != 0) &&
        ((char)param_1[iVar2 * 0x84dec + 0xdc608] == '\x01')) &&
       (param_1[iVar2 * 0x84dec + 0xdbb8f] != 0)) {
      __cntl_disconnect_request
                ((undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar2 * 0x2137b0)),1,
                 (undefined *)((int)param_1 + (int)(&DAT_0057ff80 + iVar2 * 0x2137b0)),8,
                 "RtmpIoctl_rt_private_set_wsc_u32_item",0x230b);
    }
    _WscStop(param_1,0,param_1 + iVar2 * 0x84dec + 0xdbb8f,0);
    piVar4 = param_1 + iVar2 * 0x84dec;
    piVar4[0xdbb8f] = 0;
    BssTableDeleteEntry((undefined *)((int)param_1 + (int)(&DAT_00371d80 + iVar2 * 0x2137b0)),
                        &DAT_00371c92 + (int)piVar4,*(undefined1 *)((int)piVar4 + 0x371cbd));
    return 0;
  case 0x10:
    if (2 < DebugLevel) {
      printk("%s - WSC_GEN_PIN_CODE\n","RtmpIoctl_rt_private_set_wsc_u32_item");
    }
    Set_WscGenPinCode_Proc(param_1,&_LC166);
    return 0;
  case 0x11:
    uVar3 = puVar1[1];
    if (2 < DebugLevel) {
      printk("%s - WSC_PBC_BAND, value = %d\n","RtmpIoctl_rt_private_set_wsc_u32_item",uVar3);
    }
    if (uVar3 < 3) {
      *(char *)((int)param_1 + iVar2 * 0x2137b0 + 0x371895) = (char)uVar3;
    }
  }
  return 0;
}

