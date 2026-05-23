// module: wlan_debug_module.ko
// function: cleanup_module @ 0x10000
// size: 32 bytes
//

void cleanup_module(void)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 in_r3;
  
  wlan_debug_trp_exit();
  wlan_debug_recv_exit();
  wlan_debug_pktcnt_exit();
  remove_wlan_proc_dir(&g_wlan_debug_proc_dir,extraout_r1,extraout_r2,in_r3);
  return;
}

