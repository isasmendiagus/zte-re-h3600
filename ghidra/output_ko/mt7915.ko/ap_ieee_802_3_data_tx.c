// module: mt7915.ko
// function: ap_ieee_802_3_data_tx @ 0x19e38
// size: 28 bytes
//

void ap_ieee_802_3_data_tx(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined1 *)(param_3 + 0x35) = 0;
  *(undefined1 *)(param_3 + 0x34) = 0;
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  *(undefined1 *)(param_3 + 0x2c) = 0;
  return;
}

