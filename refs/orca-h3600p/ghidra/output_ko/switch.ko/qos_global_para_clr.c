// module: switch.ko
// function: qos_global_para_clr @ 0x18944
// size: 100 bytes
//

void qos_global_para_clr(void)

{
  __memzero(&g_qos_queue,0x60);
  g_num_weight = 0;
  g_queue_index = 0;
  if (g_switch_debug_level - 2 < 2) {
    g_tcont_size = 8;
    g_tcont_start = 1;
    return;
  }
  if (g_switch_debug_level < 2) {
    g_tcont_start = 0;
    g_tcont_size = 1;
  }
  return;
}

