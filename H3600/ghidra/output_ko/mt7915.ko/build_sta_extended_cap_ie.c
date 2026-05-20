// module: mt7915.ko
// function: build_sta_extended_cap_ie @ 0x147208
// size: 472 bytes
//

undefined4 build_sta_extended_cap_ie(int param_1,int param_2,undefined1 *param_3)

{
  ushort uVar1;
  int iVar2;
  uint *puVar3;
  uint local_1b;
  uint local_17;
  ushort local_13;
  byte local_11;
  uint *puVar4;
  
  __memzero(&local_1b,0xb);
  uVar1 = *(ushort *)(param_2 + 0x18);
  if ((*(char *)(param_1 + 0x79564e) == '\x01') && ((uVar1 & 0x18) != 0)) {
    if (*(byte *)(param_2 + 0x1a) < 0xf) {
      local_1b = local_1b | 1;
      goto LAB_00147240;
    }
    if ((uVar1 & 0x20) != 0) goto LAB_00147310;
  }
  else {
LAB_00147240:
    if (((uVar1 & 0x20) != 0) && (0xe < *(byte *)(param_2 + 0x1a))) {
LAB_00147310:
      local_17 = local_17 | 0x40000000;
    }
  }
  if ((uVar1 & 0x1c0) != 0) {
    local_1b = local_1b | 0x400000;
    if (*(int *)(param_2 + 0x14) == 1) {
      iVar2 = wlan_config_get_asic_twt_caps(param_2);
      if ((iVar2 != 0) && (iVar2 = wlan_config_get_he_twt_support(param_2), iVar2 != 0)) {
        local_13 = local_13 | 0x4000;
      }
    }
    else if (((*(int *)(param_2 + 0x14) == 2) &&
             (iVar2 = wlan_config_get_asic_twt_caps(param_2), iVar2 != 0)) &&
            (iVar2 = wlan_config_get_he_twt_support(param_2), iVar2 != 0)) {
      local_13 = local_13 | 0x2000;
    }
  }
  if ((*(uint *)(param_2 + 0x2c) & 0x6000) == 0) {
    local_11 = local_11 & 0xfd;
  }
  else {
    if (*(char *)(param_2 + 0x811) == '\0') {
      local_11 = local_11 & 0xfd;
    }
    else {
      local_11 = local_11 | 2;
    }
    if (*(char *)(param_2 + 0x810) != '\0') {
      local_11 = local_11 | 4;
      goto LAB_001472d4;
    }
  }
  local_11 = local_11 & 0xfb;
LAB_001472d4:
  puVar4 = &local_1b;
  do {
    puVar3 = (uint *)((int)puVar4 + 1);
    if ((char)*puVar4 != '\0') {
      *param_3 = ExtCapIe;
      *(uint *)(param_3 + 2) = local_1b;
      param_3[1] = 0xb;
      *(uint *)(param_3 + 6) = local_17;
      *(ushort *)(param_3 + 10) = local_13;
      param_3[0xc] = local_11;
      return 0xd;
    }
    puVar4 = puVar3;
  } while (puVar3 != (uint *)&stack0xfffffff0);
  return 0;
}

