// module: switch.ko
// function: pdt_ethdrv_rate_limit_1s @ 0x10730
// size: 144 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 pdt_ethdrv_rate_limit_1s(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = jiffies;
  if (g_timestamp_1 == 0) {
    g_timestamp_1 = jiffies;
  }
  g_rev_packet_100ms = g_rev_packet_100ms + 1;
  if (param_1 < g_rev_packet_100ms) {
    g_timestamp_2 = jiffies;
    iVar2 = msecs_to_jiffies(1000);
    if ((iVar1 - g_timestamp_1) - iVar2 < 0) {
      return 0xffffffff;
    }
    g_timestamp_1 = jiffies;
    g_rev_packet_100ms = 0;
    return 0;
  }
  return 0;
}

