// module: mt7915.ko
// function: wlan_cofig_get_phy_caps @ 0x106548
// size: 20 bytes
//

undefined4 wlan_cofig_get_phy_caps(void)

{
  int iVar1;
  
  hc_get_hdev_ctrl();
  iVar1 = hc_get_chip_cap();
  return *(undefined4 *)(iVar1 + 0x2c);
}

