// module: mt7915.ko
// function: wlan_config_get_mcs_nss_caps @ 0x105c7c
// size: 20 bytes
//

int wlan_config_get_mcs_nss_caps(void)

{
  int iVar1;
  
  hc_get_hdev_ctrl();
  iVar1 = hc_get_chip_cap();
  return iVar1 + 0x6c;
}

