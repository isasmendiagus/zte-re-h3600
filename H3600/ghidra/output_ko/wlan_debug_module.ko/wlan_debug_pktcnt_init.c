// module: wlan_debug_module.ko
// function: wlan_debug_pktcnt_init @ 0x15370
// size: 136 bytes
//

undefined4 wlan_debug_pktcnt_init(void)

{
  char *__s;
  int iVar1;
  
  create_wlan_proc_dir(&g_pktcnt_proc_dir);
  create_wlan_proc_file(g_pktcnt_dbgflag_proc_file);
  create_wlan_proc_file(&g_pktcnt_dbgredirect_proc_file);
  create_wlan_proc_file(g_pktcnt_dscp_proc_file);
  __s = g_pktlist_proc + 8;
  iVar1 = 0;
  do {
    *(undefined1 **)(__s + -8) = &g_pktcnt_proc_dir;
    snprintf(__s,0x20,"pktlist%d",iVar1);
    *(int *)(__s + 0x20) = iVar1;
    iVar1 = iVar1 + 1;
    *(code **)(__s + 0x24) = pktcnt_pktlist_read;
    *(code **)(__s + 0x28) = pktcnt_pktlist_write;
    __s = __s + 0xc4;
  } while (iVar1 != 0x14);
  return 0;
}

