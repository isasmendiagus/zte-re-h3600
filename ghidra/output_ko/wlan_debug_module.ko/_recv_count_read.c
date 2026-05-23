// module: wlan_debug_module.ko
// function: _recv_count_read @ 0x11094
// size: 36 bytes
//

undefined4
_recv_count_read(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  seq_printf(param_1,&_LC4,g_wlan_debug_recv_count,&g_wlan_debug_recv_debug,param_4);
  return 0;
}

