// module: wlan_debug_module.ko
// function: wlan_debug_trp_init @ 0x10c3c
// size: 120 bytes
//

void wlan_debug_trp_init(void)

{
  create_wlan_proc_dir(g_trp_proc_dir);
  create_wlan_proc_file(&g_trp_enable_proc_file);
  create_wlan_proc_file(g_trp_pktlen_proc_file);
  create_wlan_proc_file(&g_trp_flowrate_proc_file);
  create_wlan_proc_file(g_trp_xmitdev_proc_file);
  create_wlan_proc_file(&g_trp_dstmac_proc_file);
  create_wlan_proc_file(&g_trp_dstip_proc_file);
  init_timer_key(g_dev_xmit_timer,0,0,0);
  g_dev_xmit_timer._20_4_ = 0;
  g_dev_xmit_timer._16_4_ = periodic_send_pkt;
  return;
}

