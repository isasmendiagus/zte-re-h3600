// module: mt7915.ko
// function: add_beacon_vht_ies @ 0x203af4
// size: 388 bytes
//

int add_beacon_vht_ies(undefined4 param_1,uint *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  iVar2 = wlan_config_get_vht_ldpc();
  iVar3 = wlan_config_get_vht_sgi(param_1);
  iVar4 = wlan_config_get_vht_stbc(param_1);
  uVar5 = wlan_config_get_vht_bw(param_1);
  iVar6 = wlan_config_get_ppdu_caps(param_1);
  bVar1 = *(byte *)(iVar6 + 0x14);
  iVar7 = wlan_config_get_mcs_nss_caps(param_1);
  if (iVar7 == 0 || uVar5 < 2) {
    uVar11 = 0;
  }
  else {
    uVar9 = (uint)*(byte *)(iVar7 + 1);
    uVar10 = (uint)*(byte *)(iVar7 + 3);
    if (uVar9 == uVar10) {
      uVar11 = 8;
      wlan_config_set_vht_ext_nss_bw(param_1,0);
      uVar9 = (uint)*(byte *)(iVar7 + 1);
      uVar10 = (uint)*(byte *)(iVar7 + 3);
    }
    else {
      uVar11 = 0;
    }
    if (uVar10 == uVar9 >> 1) {
      wlan_config_set_vht_ext_nss_bw(param_1,2);
      uVar11 = uVar11 | 0x80000000;
      uVar9 = (uint)*(byte *)(iVar7 + 1);
      uVar10 = (uint)*(byte *)(iVar7 + 3);
    }
    if (uVar10 == uVar9 * 2) {
      wlan_config_set_vht_ext_nss_bw(param_1,3);
      uVar11 = 0x80000008;
    }
  }
  uVar11 = uVar11 | bVar1 & 3;
  if (iVar2 != 0) {
    uVar11 = uVar11 | 0x10;
  }
  if (iVar3 != 0) {
    if (uVar5 < 2) {
      uVar11 = uVar11 | 0x20;
    }
    else {
      uVar11 = uVar11 | 0x60;
    }
  }
  if (iVar4 != 0) {
    uVar11 = uVar11 | 0x180;
  }
  *param_2 = uVar11 | (uint)*(byte *)(iVar6 + 0x15) << 0x17;
  uVar8 = FUN_00201a3c(param_1,param_2 + 1);
  uVar8 = build_vht_op_info(param_1,uVar8);
  iVar2 = FUN_00201a3c(param_1,uVar8);
  return iVar2 - (int)param_2;
}

