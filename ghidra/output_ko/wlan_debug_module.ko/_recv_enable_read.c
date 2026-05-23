// module: wlan_debug_module.ko
// function: _recv_enable_read @ 0x110b8
// size: 36 bytes
//

undefined4
_recv_enable_read(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  seq_printf(param_1,&_LC4,g_wlan_debug_recv_enable,&g_wlan_debug_recv_debug,param_4);
  return 0;
}

