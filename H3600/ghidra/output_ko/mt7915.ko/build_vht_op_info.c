// module: mt7915.ko
// function: build_vht_op_info @ 0x203a3c
// size: 184 bytes
//

undefined1 * build_vht_op_info(int param_1,undefined1 *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined1 uVar6;
  undefined1 unaff_r9;
  bool bVar7;
  
  bVar1 = *(byte *)(param_1 + 0x1a);
  uVar2 = wlan_operate_get_cen_ch_1();
  iVar3 = wlan_operate_get_vht_bw(param_1);
  uVar4 = wlan_config_get_tx_stream(param_1);
  iVar5 = wlan_config_get_mcs_nss_caps(param_1);
  uVar6 = 0;
  if (iVar3 != 0) {
    bVar7 = *(byte *)(iVar5 + 3) != uVar4;
    if (iVar3 == 2) {
      uVar6 = 1;
      if (uVar2 < bVar1) {
        uVar4 = uVar2 + 8;
      }
      else {
        uVar4 = uVar2 - 8;
      }
      if (bVar7) {
        uVar2 = 0;
      }
      unaff_r9 = (undefined1)uVar2;
      uVar2 = uVar4 & 0xff;
    }
    else if (iVar3 == 3) {
      uVar6 = 1;
      unaff_r9 = wlan_operate_get_cen_ch_2(param_1);
      if (bVar7) {
        unaff_r9 = 0;
      }
    }
    else {
      uVar6 = 1;
    }
  }
  *param_2 = uVar6;
  param_2[1] = (char)uVar2;
  param_2[2] = unaff_r9;
  return param_2 + 3;
}

