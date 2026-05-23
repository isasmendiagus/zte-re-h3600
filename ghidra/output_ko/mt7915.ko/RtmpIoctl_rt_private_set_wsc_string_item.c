// module: mt7915.ko
// function: RtmpIoctl_rt_private_set_wsc_string_item @ 0x65174
// size: 1316 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 RtmpIoctl_rt_private_set_wsc_string_item(int *param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *puVar4;
  int *__dest;
  uint uVar6;
  size_t __n;
  undefined1 *puVar7;
  char *pcVar8;
  int iVar9;
  bool bVar10;
  undefined4 local_38 [7];
  undefined4 *puVar5;
  
  uVar3 = *param_2;
  pcVar8 = (char *)param_2[1];
  bVar10 = 0x11 < uVar3;
  if (uVar3 != 0x12) {
    bVar10 = uVar3 != 0xc;
  }
  iVar9 = *(int *)(*param_1 + 0x3c);
  uVar6 = (int)*pcVar8 - 0x30;
  if (bVar10 && (uVar3 != 0x12 && uVar3 != 0xd)) {
    if (7 < uVar6) {
      if (2 < DebugLevel) {
        printk("%s - subcmd = %d, tmpProfileIndex = %d\n","RtmpIoctl_rt_private_set_wsc_string_item"
               ,uVar3,uVar6);
      }
      goto LAB_0006521c;
    }
    __n = param_2[2] - 3;
  }
  else {
    __n = param_2[2];
  }
  switch(uVar3) {
  case 2:
    if (2 < DebugLevel) {
      printk("%s - WSC_CREDENTIAL_SSID(%s)\n","RtmpIoctl_rt_private_set_wsc_string_item",pcVar8 + 2)
      ;
    }
    if (__n == 0x21) {
      __n = 0x20;
    }
    else if (0x1f < __n - 1) goto LAB_0006529c;
    uVar2 = 0x20;
    __dest = param_1 + uVar6 * 0x1d + iVar9 * 0x84dec + 0xdc2b6;
    *(size_t *)(&DAT_00370ad4 + (int)(param_1 + uVar6 * 0x1d + iVar9 * 0x84dec)) = __n;
    goto LAB_0006541c;
  case 3:
    if (2 < DebugLevel) {
      printk("%s - WSC_CREDENTIAL_AUTH_MODE(%s)\n","RtmpIoctl_rt_private_set_wsc_string_item",
             pcVar8 + 2);
    }
    iVar1 = WscGetAuthTypeFromStr(pcVar8 + 2);
    if (iVar1 != 0) {
      *(short *)(&DAT_00370af8 + (int)(param_1 + uVar6 * 0x1d + iVar9 * 0x84dec)) = (short)iVar1;
      return 0;
    }
    break;
  case 4:
    if (2 < DebugLevel) {
      printk("%s - WSC_CREDENTIAL_ENCR_TYPE(%s)\n","RtmpIoctl_rt_private_set_wsc_string_item",
             pcVar8 + 2);
    }
    iVar1 = WscGetEncrypTypeFromStr(pcVar8 + 2);
    if (iVar1 != 0) {
      *(short *)(&DAT_00370afa + (int)(param_1 + uVar6 * 0x1d + iVar9 * 0x84dec)) = (short)iVar1;
      return 0;
    }
    break;
  case 5:
    if (2 < DebugLevel) {
      printk("%s - WSC_CREDENTIAL_KEY_INDEX(%s)\n","RtmpIoctl_rt_private_set_wsc_string_item",
             pcVar8 + 2);
    }
    if ((byte)pcVar8[2] - 0x31 < 4) {
      (&DAT_00370b44)[(int)(param_1 + uVar6 * 0x1d + iVar9 * 0x84dec)] = pcVar8[2] - 0x30;
      return 0;
    }
    break;
  case 6:
    if (2 < DebugLevel) {
      printk("%s - WSC_CREDENTIAL_KEY(%s)\n","RtmpIoctl_rt_private_set_wsc_string_item",pcVar8 + 2);
    }
    if ((0x38 < __n - 8) && (__n != 5)) break;
    uVar2 = 0x40;
    __dest = param_1 + uVar6 * 0x1d + iVar9 * 0x84dec + 0xdc2bf;
    *(short *)(&DAT_00370b3c + (int)(param_1 + uVar6 * 0x1d + iVar9 * 0x84dec)) = (short)__n;
LAB_0006541c:
    __memzero(__dest,uVar2);
    memmove(__dest,pcVar8 + 2,__n);
    return 0;
  case 7:
    if (2 < DebugLevel) {
      printk("%s - WSC_CREDENTIAL_MAC(%s)\n","RtmpIoctl_rt_private_set_wsc_string_item",pcVar8 + 2);
    }
    local_38[0] = 0;
    local_38[1] = 0;
    local_38[2] = 0;
    local_38[3] = 0;
    local_38[4] = 0;
    local_38[5] = 0;
    iVar1 = sscanf(pcVar8 + 2,"%02x:%02x:%02x:%02x:%02x:%02x",local_38,local_38 + 1,local_38 + 2,
                   local_38 + 3,local_38 + 4,local_38 + 5);
    if (iVar1 == 6) {
      __memzero(&DAT_00370b3e + (int)(param_1 + iVar9 * 0x84dec + uVar6 * 0x1d),6);
      puVar7 = (undefined1 *)((int)param_1 + iVar9 * 0x2137b0 + 0x370b3d + uVar6 * 0x74);
      puVar4 = local_38;
      do {
        puVar5 = puVar4 + 1;
        puVar7 = puVar7 + 1;
        *puVar7 = (char)*puVar4;
        puVar4 = puVar5;
      } while (puVar5 != local_38 + 6);
      return 0;
    }
    break;
  default:
    if (DebugLevel < 3) {
      return 0;
    }
    printk("%s - unknow subcmd = %d\n","RtmpIoctl_rt_private_set_wsc_string_item",uVar3);
    return 0;
  case 0xc:
    if (2 < DebugLevel) {
      printk("%s - WSC_SET_PIN, value = (%s)\n","RtmpIoctl_rt_private_set_wsc_string_item",pcVar8);
    }
    if ((__n != 0) && (iVar9 = Set_WscPinCode_Proc(param_1,pcVar8), iVar9 != 0)) {
      return 0;
    }
    break;
  case 0xd:
    if (2 < DebugLevel) {
      printk("%s - WSC_SET_SSID(%s)\n","RtmpIoctl_rt_private_set_wsc_string_item",pcVar8);
    }
    if (__n - 1 < 0x21) {
      Set_WscSsid_Proc(param_1,pcVar8);
      return 0;
    }
LAB_0006529c:
    param_2[3] = 0x7534;
    return 0;
  case 0x12:
    if ((__n == 0) || (iVar9 = Set_WscBssid_Proc(param_1,pcVar8), iVar9 == 0)) {
      param_2[3] = 30000;
    }
    if (DebugLevel < 3) {
      return 0;
    }
    printk("%s - WSC_SET_BSSID\n","RtmpIoctl_rt_private_set_wsc_string_item");
    return 0;
  }
LAB_0006521c:
  param_2[3] = 30000;
  return 0;
}

