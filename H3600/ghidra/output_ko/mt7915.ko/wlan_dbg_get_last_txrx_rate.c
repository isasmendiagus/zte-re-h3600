// module: mt7915.ko
// function: wlan_dbg_get_last_txrx_rate @ 0x1585b8
// size: 20 bytes
//

void wlan_dbg_get_last_txrx_rate(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  *param_2 = *(undefined4 *)(param_1 + 0x134);
  *param_3 = *(undefined4 *)(param_1 + 0x138);
  return;
}

