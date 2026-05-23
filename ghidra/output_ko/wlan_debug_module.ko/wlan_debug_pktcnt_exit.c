// module: wlan_debug_module.ko
// function: wlan_debug_pktcnt_exit @ 0x15408
// size: 148 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 wlan_debug_pktcnt_exit(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  _init_timer_key = 0;
  remove_wlan_proc_file(g_pktcnt_dbgflag_proc_file);
  remove_wlan_proc_file(&g_pktcnt_dbgredirect_proc_file);
  remove_wlan_proc_file(g_pktcnt_dscp_proc_file);
  g_pktcnt_dbgflag = 0;
  g_pktcnt_dbgredirect = 0;
  g_pktcnt_dbgnum = 0;
  g_count = 0;
  g_dscp_set_flag = 0;
  g_dscp_of_tcp = 0;
  g_dscp_of_udp = 0;
  g_normal_pkt_cnt._0_4_ = 0;
  g_normal_pkt_cnt._4_4_ = 0;
  g_shared_pkt_cnt._0_4_ = 0;
  g_shared_pkt_cnt._4_4_ = 0;
  puVar1 = g_pktlist_proc;
  do {
    puVar2 = puVar1 + 0xc4;
    remove_wlan_proc_file(puVar1);
    puVar1 = puVar2;
  } while (puVar2 != (undefined1 *)0x67064);
  remove_wlan_proc_dir(&g_pktcnt_proc_dir);
  return 0;
}

