// module: tm.ko
// function: zte_api_set_debuglevel @ 0x60870
// size: 20 bytes
//

undefined4 zte_api_set_debuglevel(undefined4 param_1)

{
  g_tm_debug_level = param_1;
  return 0;
}

