// module: mt7915.ko
// function: wlan_dbg_set_last_error @ 0x1584fc
// size: 148 bytes
//

void wlan_dbg_set_last_error(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 == 1) {
    param_1 = param_1 * 0x74;
    *(undefined4 *)(g_stWlanRadioStat + param_1 + 0x68) = param_4;
    *(undefined4 *)(g_stWlanRadioStat + param_1 + 100) = param_3;
    *(int *)(g_stWlanRadioStat + param_1 + 0x38) = *(int *)(g_stWlanRadioStat + param_1 + 0x38) + 1;
    return;
  }
  if (param_2 != 0) {
    if (param_2 != 2) {
      return;
    }
    param_1 = param_1 * 0x74;
    *(undefined4 *)(g_stWlanRadioStat + param_1 + 0x70) = param_3;
    *(int *)(g_stWlanRadioStat + param_1 + 0x4c) = *(int *)(g_stWlanRadioStat + param_1 + 0x4c) + 1;
    return;
  }
  param_1 = param_1 * 0x74;
  *(undefined4 *)(g_stWlanRadioStat + param_1 + 0x60) = param_4;
  *(undefined4 *)(g_stWlanRadioStat + param_1 + 0x5c) = param_3;
  *(int *)(g_stWlanRadioStat + param_1 + 4) = *(int *)(g_stWlanRadioStat + param_1 + 4) + 1;
  return;
}

