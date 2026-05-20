// module: wlan_debug_module.ko
// function: wlan_debug_recv_exit @ 0x113a8
// size: 92 bytes
//

undefined4 wlan_debug_recv_exit(void)

{
  wlan_cspkernel_ops = 0;
  remove_wlan_proc_file(&g_recv_enable_proc_file);
  remove_wlan_proc_file(&g_recv_count_proc_file);
  remove_wlan_proc_file(g_recv_mac_proc_file);
  remove_wlan_proc_file(&g_recv_debug_proc_file);
  remove_wlan_proc_dir(g_recv_proc_dir);
  g_wlan_debug_recv_count = 0;
  g_wlan_debug_recv_enable = 0;
  return 0;
}

