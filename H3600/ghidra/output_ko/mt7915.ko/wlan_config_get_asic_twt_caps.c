// module: mt7915.ko
// function: wlan_config_get_asic_twt_caps @ 0x105cb4
// size: 20 bytes
//

uint wlan_config_get_asic_twt_caps(void)

{
  int iVar1;
  
  hc_get_hdev_ctrl();
  iVar1 = hc_get_asic_cap();
  return (uint)(iVar1 << 0xd) >> 0x1f;
}

