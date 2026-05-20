// module: wlan_debug_module.ko
// function: _recv_mac_read @ 0x11048
// size: 76 bytes
//

undefined4 _recv_mac_read(undefined4 param_1)

{
  seq_printf(param_1,"%02x:%02x:%02x:%02x:%02x:%02x\n",(undefined1)g_wlan_debug_recv_mac,
             g_wlan_debug_recv_mac._1_1_,g_wlan_debug_recv_mac._2_1_,g_wlan_debug_recv_mac._3_1_,
             (undefined1)DAT_0001746c,DAT_0001746c._1_1_);
  return 0;
}

