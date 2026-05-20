// module: mt7915.ko
// function: wlan_config_get_asic_caps @ 0x105c40
// size: 20 bytes
//

undefined4 wlan_config_get_asic_caps(void)

{
  int iVar1;
  
  hc_get_hdev_ctrl();
  iVar1 = hc_get_chip_cap();
  return *(undefined4 *)(iVar1 + 0x24);
}

