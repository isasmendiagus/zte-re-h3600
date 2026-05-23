// module: wlan_debug_module.ko
// function: init_module @ 0x154ac
// size: 36 bytes
//

undefined4 init_module(void)

{
  create_wlan_proc_dir(&g_wlan_debug_proc_dir);
  wlan_debug_trp_init();
  wlan_debug_recv_init();
  wlan_debug_pktcnt_init();
  return 0;
}

