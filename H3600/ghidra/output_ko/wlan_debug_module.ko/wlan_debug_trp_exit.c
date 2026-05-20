// module: wlan_debug_module.ko
// function: wlan_debug_trp_exit @ 0x10cb4
// size: 100 bytes
//

undefined4 wlan_debug_trp_exit(void)

{
  g_wlan_debug_trp_enable = 0;
  del_timer(g_dev_xmit_timer);
  remove_wlan_proc_file(&g_trp_enable_proc_file);
  remove_wlan_proc_file(g_trp_pktlen_proc_file);
  remove_wlan_proc_file(&g_trp_flowrate_proc_file);
  remove_wlan_proc_file(g_trp_xmitdev_proc_file);
  remove_wlan_proc_file(&g_trp_dstmac_proc_file);
  remove_wlan_proc_file(&g_trp_dstip_proc_file);
  remove_wlan_proc_dir(g_trp_proc_dir);
  return 0;
}

