// module: mt7915.ko
// function: wlan_config_get_chip_caps @ 0x105ca4
// size: 16 bytes
//

void wlan_config_get_chip_caps(void)

{
  hc_get_hdev_ctrl();
  hc_get_chip_cap();
  return;
}

