// module: mt7915.ko
// function: ZTE_Get_Driver_Stat @ 0x15ea74
// size: 900 bytes
//

void ZTE_Get_Driver_Stat(int *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  undefined1 auStack_88 [4];
  ushort local_84 [2];
  int local_80 [3];
  int local_74;
  int local_70;
  int local_68;
  undefined4 local_64;
  int local_60;
  int iStack_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_48;
  undefined4 local_44;
  int local_40;
  undefined4 local_3c;
  undefined4 local_2c;
  undefined1 auStack_24 [4];
  
  uVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  __memzero(local_80,0x60);
  if (*(ushort *)(param_2 + 0x14) < 0x60) {
    if (DebugLevel < 0) {
      return;
    }
    printk("ZTE_Get_Driver_Stat failed  length=%d \n");
    return;
  }
  iVar2 = HcGetBandByWdev(uVar1);
  mac_io_read32(param_1[0x29e5e8],iVar2 * 0x10000 + -0x7df12ff0,local_84);
  local_44 = 0;
  local_48 = (uint)local_84[0] + param_1[iVar2 * 3 + 0xdb6ce];
  param_1[iVar2 * 3 + 0xdb6ce] = local_48;
  if (((param_1[0x28eb05] & 1U) == 0) &&
     ((param_1[0x29deed] != 1 || ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) == 0)))) {
    local_80[0] = param_1[iVar2 * 0x42 + 0x28e700];
    if ((param_1[0xa5b19] & 0xffffU) == 0x7915) {
      local_68 = param_1[iVar2 * 0x42 + 0x28e704];
      local_40 = param_1[iVar2 * 0x42 + 0x28e706];
      local_60 = param_1[iVar2 * 0x42 + 0x28e732];
LAB_0015ed7c:
      iStack_5c = 0;
      uVar3 = 0x9cb8;
      goto LAB_0015ebcc;
    }
    local_60 = param_1[iVar2 * 0x42 + 0x28e712];
    iStack_5c = param_1[iVar2 * 0x42 + 0x28e713];
    local_68 = param_1[iVar2 * 0x42 + 0x28e704];
    local_40 = param_1[iVar2 * 0x42 + 0x28e706];
  }
  else {
    iVar4 = net_ad_wrap_service(param_1);
    local_68 = param_1[iVar2 * 0x42 + 0x28e704];
    local_40 = param_1[iVar2 * 0x42 + 0x28e706];
    local_60 = 0;
    iStack_5c = 0;
    local_80[0] = *(int *)(iVar2 * 0xd18 + iVar4 + 0x111c);
    if ((param_1[0xa5b19] & 0xffffU) == 0x7915) goto LAB_0015ed7c;
  }
  uVar3 = 0x9c58;
LAB_0015ebcc:
  iVar4 = local_80[0];
  local_3c = 0;
  local_64 = 0;
  local_80[1] = 0;
  local_54 = 0;
  local_58 = *(undefined4 *)((int)param_1 + (uVar3 | 0xa30000) + iVar2 * 0x108);
  local_2c = ZTE_Get_ChannelInterfer(param_1);
  if (iVar4 == 0) {
    local_80[2] = 0;
  }
  else {
    local_80[2] = __aeabi_uidiv(param_1[iVar2 * 0x42 + 0x28e704] * 100,
                                param_1[iVar2 * 0x42 + 0x28e704] + iVar4);
  }
  iVar4 = (short)iVar2 * 5;
  if (iVar4 < iVar4 + 5) {
    iVar4 = (short)iVar2 * 0x1b904;
    piVar5 = (int *)((int)param_1 +
                    (int)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + iVar4 + 0xc));
    do {
      iVar7 = *piVar5;
      piVar8 = piVar5 + 1;
      piVar5 = piVar5 + 0x160d;
      local_74 = local_74 + iVar7;
      local_70 = local_70 + *piVar8;
    } while (piVar5 != (int *)((int)param_1 +
                              (int)(
                                   "RTMPAddWcidAttributeEntry: The BSS-index(%d) is out of range for Infra link.\n"
                                   + iVar4 + 0x40)));
  }
  RTMP_GET_TEMPERATURE(param_1,iVar2,auStack_24);
  uVar3 = *(uint *)(param_2 + 0x10);
  uVar6 = *(uint *)(((uint)auStack_88 & 0xffffe000) + 8);
  if (uVar3 < 0xffffffa0 && uVar3 + 0x60 <= uVar6) {
    uVar6 = 0;
  }
  if (((uVar6 != 0) || (iVar2 = __copy_to_user(uVar3,local_80,0x60), iVar2 != 0)) &&
     (-1 < DebugLevel)) {
    printk("ZTE_Get_Driver_Stat failed\n");
  }
  return;
}

