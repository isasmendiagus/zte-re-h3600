// module: wlan_debug_module.ko
// function: _trp_enable_read @ 0x108a8
// size: 36 bytes
//

undefined4
_trp_enable_read(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  seq_printf(param_1,&_LC15,g_wlan_debug_trp_enable,&g_pkts_per_cycle,param_4);
  return 0;
}

