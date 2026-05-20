// module: wlan_debug_module.ko
// function: wlan_debug_recv_init @ 0x11358
// size: 80 bytes
//

undefined4 wlan_debug_recv_init(void)

{
  create_wlan_proc_dir(g_recv_proc_dir);
  create_wlan_proc_file(&g_recv_enable_proc_file);
  create_wlan_proc_file(&g_recv_count_proc_file);
  create_wlan_proc_file(g_recv_mac_proc_file);
  create_wlan_proc_file(&g_recv_debug_proc_file);
  wlan_cspkernel_ops = wlan_debug_recv_check;
  return 0;
}

