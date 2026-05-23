// module: mt7915.ko
// function: MakeExtCapIE @ 0xb3b1c
// size: 844 bytes
//

void MakeExtCapIE(int param_1,int param_2,int *param_3,int param_4)

{
  ushort uVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  byte extraout_r2;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  uint uVar10;
  bool bVar11;
  byte local_31;
  int local_30;
  char acStack_2c [8];
  byte local_24;
  byte local_22;
  byte local_21;
  
  uVar1 = *(ushort *)(param_2 + 0x18);
  iVar9 = *param_3;
  local_31 = 0xb;
  __memzero(acStack_2c + 1,0xb);
  if (((((uVar1 & 0x18) != 0) && (*(byte *)(param_2 + 0x1a) < 0xf)) &&
      (*(char *)(param_2 + 0x891) != '\0')) && (*(char *)(param_1 + 0x79564e) == '\x01')) {
    acStack_2c[1] = acStack_2c[1] | 1;
  }
  if (*(char *)(param_2 + 0x4c9c) != '\0') {
    acStack_2c[2] = acStack_2c[2] | 0x10;
  }
  if (*(char *)(param_2 + 0x4c9e) != '\0') {
    acStack_2c[3] = acStack_2c[3] | 8;
  }
  if (((uVar1 & 0x20) != 0) && (0xe < *(byte *)(param_2 + 0x1a))) {
    local_24 = local_24 | 0x40;
  }
  iVar3 = HcGetBandByWdev(param_2);
  if (((*(int *)(param_1 + (iVar3 + 0xd9e3a) * 4) == 0) ||
      (uVar10 = *(uint *)(param_2 + 0x4060), iVar3 = HcGetBandByWdev(param_2),
      uVar10 != (byte)(&DAT_003678f2)[param_1 + iVar3])) ||
     (iVar3 = HcGetBandByWdev(param_2),
     (*(uint *)(param_1 + (iVar3 + 0xd9e3a) * 4) & ~(1 << (*(uint *)(param_2 + 0x4064) & 0xff))) ==
     0)) {
    acStack_2c[3] = acStack_2c[3] & 0xbf;
  }
  else {
    acStack_2c[3] = acStack_2c[3] | 0x40;
  }
  iVar3 = HcGetBandByWdev(param_2);
  bVar11 = *(int *)(param_1 + (iVar3 + 0xd9e3a) * 4) != 0;
  if (bVar11) {
    local_21 = local_21 | 1;
    bVar2 = extraout_r2;
  }
  else {
    bVar2 = local_21 & 0xfe;
  }
  if (!bVar11) {
    local_21 = bVar2;
  }
  if ((*(ushort *)(param_2 + 0x18) & 0x1c0) != 0) {
    if (*(int *)(param_2 + 0x14) == 1) {
      iVar3 = wlan_config_get_asic_twt_caps(param_2);
      if ((iVar3 != 0) && (iVar3 = wlan_config_get_he_twt_support(param_2), iVar3 != 0)) {
        local_22 = local_22 | 0x40;
      }
    }
    else if (((*(int *)(param_2 + 0x14) == 2) &&
             (iVar3 = wlan_config_get_asic_twt_caps(param_2), iVar3 != 0)) &&
            (iVar3 = wlan_config_get_he_twt_support(param_2), iVar3 != 0)) {
      local_22 = local_22 | 0x20;
    }
  }
  if ((*(uint *)(param_2 + 0x2c) & 0x6000) == 0) {
    local_21 = local_21 & 0xfd;
  }
  else {
    if (*(char *)(param_2 + 0x811) == '\0') {
      local_21 = local_21 & 0xfd;
    }
    else {
      local_21 = local_21 | 2;
    }
    if (*(char *)(param_2 + 0x810) != '\0') {
      local_21 = local_21 | 4;
      goto LAB_000b3c84;
    }
  }
  local_21 = local_21 & 0xfb;
LAB_000b3c84:
  uVar10 = (uint)local_31;
  if (uVar10 == 0) {
LAB_000b3cc4:
    *param_3 = iVar9;
    return;
  }
  uVar6 = uVar10 - 1;
  if (acStack_2c[1] == 0) {
    pcVar5 = acStack_2c + 1;
    pcVar8 = pcVar5 + uVar6;
    do {
      if (pcVar5 == pcVar8) goto LAB_000b3cc4;
      pcVar5 = pcVar5 + 1;
    } while (*pcVar5 == '\0');
  }
  if ((10 < uVar6) && (acStack_2c[uVar10] == '\0')) {
    pcVar5 = acStack_2c + uVar10;
    uVar4 = uVar10 - 2;
    do {
      uVar7 = uVar6;
      uVar10 = uVar7 & 0xff;
      if (uVar4 < 0xb) break;
      pcVar5 = pcVar5 + -1;
      uVar4 = uVar4 - 1;
      uVar6 = uVar10 - 1;
    } while (*pcVar5 == '\0');
    local_31 = (byte)uVar7;
  }
  MakeOutgoingFrame(param_4 + iVar9,&local_30,1,&ExtCapIe,1,&local_31,uVar10,acStack_2c + 1,
                    0xffffffff);
  *param_3 = iVar9 + local_30;
  return;
}

