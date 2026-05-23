// module: mt7915.ko
// function: wlan_config_set_he_rx_nss @ 0x2063a0
// size: 36 bytes
//

void wlan_config_set_he_rx_nss(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xb10);
  iVar1 = wlan_config_get_mcs_nss_caps();
  if (*(byte *)(iVar1 + 1) <= param_2) {
    param_2 = (uint)*(byte *)(iVar1 + 1);
  }
  *(char *)(iVar2 + 0x6c) = (char)param_2;
  return;
}

