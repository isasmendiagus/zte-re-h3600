// module: bspdriver.ko
// function: set_protectClk_interval @ 0x10924
// size: 20 bytes
//

undefined4 set_protectClk_interval(undefined4 param_1)

{
  g_protectClk_interval = param_1;
  return 0;
}

