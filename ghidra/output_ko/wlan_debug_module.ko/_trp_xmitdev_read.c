// module: wlan_debug_module.ko
// function: _trp_xmitdev_read @ 0x10840
// size: 32 bytes
//

undefined4
_trp_xmitdev_read(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  seq_printf(param_1,&_LC14,g_wlan_debug_trp_xmitdev,param_4,param_4);
  return 0;
}

