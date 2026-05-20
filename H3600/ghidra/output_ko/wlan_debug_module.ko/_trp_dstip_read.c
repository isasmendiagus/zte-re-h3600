// module: wlan_debug_module.ko
// function: _trp_dstip_read @ 0x107b0
// size: 68 bytes
//

undefined4 _trp_dstip_read(undefined4 param_1)

{
  seq_printf(param_1,"[%u.%u.%u.%u]\n",g_wlan_debug_trp_dstip >> 0x18,
             (g_wlan_debug_trp_dstip << 8) >> 0x18,(g_wlan_debug_trp_dstip << 0x10) >> 0x18,
             g_wlan_debug_trp_dstip & 0xff);
  return 0;
}

