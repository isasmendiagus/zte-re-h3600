// module: wlan_debug_module.ko
// function: _trp_dstmac_read @ 0x107f4
// size: 76 bytes
//

undefined4 _trp_dstmac_read(undefined4 param_1)

{
  seq_printf(param_1,"%02X:%02X:%02X:%02X:%02X:%02X\n",(undefined1)g_wlan_debug_trp_dstmac,
             g_wlan_debug_trp_dstmac._1_1_,g_wlan_debug_trp_dstmac._2_1_,
             g_wlan_debug_trp_dstmac._3_1_,g_wlan_debug_trp_dstmac._4_1_,
             g_wlan_debug_trp_dstmac._5_1_);
  return 0;
}

