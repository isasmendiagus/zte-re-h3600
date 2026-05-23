// module: bspdriver.ko
// function: get_protectClk_interval @ 0x10938
// size: 24 bytes
//

undefined4 get_protectClk_interval(undefined4 *param_1)

{
  *param_1 = g_protectClk_interval;
  return 0;
}

