// module: switch.ko
// function: ethdrv_set_wanportid @ 0x104a0
// size: 16 bytes
//

void ethdrv_set_wanportid(undefined1 param_1)

{
  g_sw_netInfo[0x2c] = param_1;
  return;
}

