// module: mt7915.ko
// function: wlan_dbg_radio_statistics_inc @ 0x158590
// size: 40 bytes
//

void wlan_dbg_radio_statistics_inc(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (param_1 * 0x1d + param_2) * 4;
  *(int *)(g_stWlanRadioStat + iVar1) = *(int *)(g_stWlanRadioStat + iVar1) + 1;
  return;
}

