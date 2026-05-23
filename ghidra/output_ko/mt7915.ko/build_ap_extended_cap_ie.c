// module: mt7915.ko
// function: build_ap_extended_cap_ie @ 0x146f4c
// size: 700 bytes
//

undefined4 build_ap_extended_cap_ie(int param_1,int param_2,undefined1 *param_3,int param_4)

{
  int iVar1;
  bool *pbVar2;
  size_t __n;
  undefined1 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  bool local_2b [2];
  byte local_29;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  byte local_22;
  byte local_21;
  bool abStack_20 [4];
  bool *pbVar3;
  
  iVar6 = *(int *)(param_2 + 4);
  local_2b[0] = false;
  local_2b[1] = false;
  local_29 = 0;
  local_28 = 0;
  local_27 = 0;
  local_26 = 0;
  local_25 = 0;
  local_24 = 0;
  local_23 = 0;
  local_22 = 0;
  local_21 = 0;
  if (((*(char *)(param_1 + 0x79564e) == '\x01') && ((*(ushort *)(param_2 + 0x18) & 0x18) != 0)) &&
     (*(byte *)(param_2 + 0x1a) < 0xf)) {
    local_2b[0] = *(char *)(param_2 + 0x891) != '\0';
  }
  if (*(char *)(iVar6 + 0x4c9c) != '\0') {
    local_2b[1] = true;
  }
  if (*(char *)(iVar6 + 0x4c9e) != '\0') {
    local_29 = 8;
  }
  if (*(char *)(iVar6 + 0x4c58) != '\0') {
    local_28 = 0x80;
  }
  if (((*(ushort *)(param_2 + 0x18) & 0x20) != 0) && (0xe < *(byte *)(param_2 + 0x1a))) {
    local_24 = 0x40;
  }
  iVar1 = HcGetBandByWdev(param_2);
  if (((*(int *)(param_1 + (iVar1 + 0xd9e3a) * 4) != 0) &&
      (uVar7 = *(uint *)(iVar6 + 0x4060), iVar1 = HcGetBandByWdev(param_2),
      uVar7 == (byte)(&DAT_003678f2)[param_1 + iVar1])) &&
     (iVar1 = HcGetBandByWdev(param_2),
     (*(uint *)(param_1 + (iVar1 + 0xd9e3a) * 4) & ~(1 << (*(uint *)(iVar6 + 0x4064) & 0xff))) != 0)
     ) {
    local_29 = local_29 | 0x40;
  }
  iVar6 = HcGetBandByWdev(param_2);
  if (*(int *)(param_1 + (iVar6 + 0xd9e3a) * 4) != 0) {
    local_21 = local_21 | 1;
  }
  if ((*(ushort *)(param_2 + 0x18) & 0x1c0) != 0) {
    if (*(int *)(param_2 + 0x14) == 1) {
      iVar6 = wlan_config_get_asic_twt_caps(param_2);
      if ((iVar6 != 0) && (iVar6 = wlan_config_get_he_twt_support(param_2), iVar6 != 0)) {
        local_22 = local_22 | 0x40;
      }
    }
    else if (((*(int *)(param_2 + 0x14) == 2) &&
             (iVar6 = wlan_config_get_asic_twt_caps(param_2), iVar6 != 0)) &&
            (iVar6 = wlan_config_get_he_twt_support(param_2), iVar6 != 0)) {
      local_22 = local_22 | 0x20;
    }
  }
  if ((*(uint *)(param_2 + 0x2c) & 0x6000) != 0) {
    if (*(char *)(param_2 + 0x811) != '\0') {
      local_21 = local_21 | 2;
    }
    if (*(char *)(param_2 + 0x810) != '\0') {
      local_21 = local_21 | 4;
    }
  }
  pbVar3 = local_2b;
  do {
    pbVar2 = pbVar3 + 1;
    if (*pbVar3 != false) {
      *param_3 = ExtCapIe;
      if (param_4 == 0) {
        __n = 0xb;
        uVar5 = 0xd;
        uVar4 = 0xb;
      }
      else {
        __n = 8;
        uVar5 = 10;
        uVar4 = 8;
      }
      param_3[1] = uVar4;
      memcpy(param_3 + 2,local_2b,__n);
      return uVar5;
    }
    pbVar3 = pbVar2;
  } while (pbVar2 != local_2b + 0xb);
  return 0;
}

