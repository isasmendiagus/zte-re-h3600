// module: mt7915.ko
// function: wlan_config_get_qos_caps @ 0x105c90
// size: 20 bytes
//

int wlan_config_get_qos_caps(void)

{
  int iVar1;
  
  hc_get_hdev_ctrl();
  iVar1 = hc_get_chip_cap();
  return iVar1 + 0x74;
}

