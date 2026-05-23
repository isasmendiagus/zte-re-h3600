// module: wlan_debug_module.ko
// function: _recv_debug_read @ 0x11024
// size: 36 bytes
//

undefined4
_recv_debug_read(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  seq_printf(param_1,"0x%x\n",g_wlan_debug_recv_debug,&g_wlan_debug_recv_debug,param_4);
  return 0;
}

