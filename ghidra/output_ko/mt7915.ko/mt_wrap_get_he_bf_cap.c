// module: mt7915.ko
// function: mt_wrap_get_he_bf_cap @ 0x8a60c
// size: 140 bytes
//

void mt_wrap_get_he_bf_cap(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined1 auStack_50 [4];
  undefined1 local_4c;
  undefined4 local_34;
  undefined4 local_28;
  
  iVar1 = wlan_config_get_mcs_nss_caps();
  uVar2 = wlan_config_get_he_bw(param_1);
  uVar3 = wlan_config_get_tx_stream(param_1);
  hc_get_hdev_ctrl(param_1);
  iVar4 = hc_get_chip_ops();
  if ((2 < uVar2) && (uVar2 = *(byte *)(iVar1 + 3) + 1, (int)uVar2 < (int)uVar3)) {
    uVar3 = uVar2 & 0xff;
  }
  local_4c = (undefined1)uVar3;
  local_34 = param_2;
  local_28 = wlan_config_get_etxbf(param_1);
  if (*(code **)(iVar4 + 0x100) != (code *)0x0) {
    (**(code **)(iVar4 + 0x100))(param_1,auStack_50);
  }
  return;
}

