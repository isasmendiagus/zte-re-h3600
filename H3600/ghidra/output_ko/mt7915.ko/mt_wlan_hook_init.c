// module: mt7915.ko
// function: mt_wlan_hook_init @ 0x2469f0
// size: 36 bytes
//

void mt_wlan_hook_init(void)

{
  os_zero_mem(&wlan_hook,8);
  wlan_hook._0_4_ = &wlan_hook;
  wlan_hook._4_4_ = &wlan_hook;
  return;
}

