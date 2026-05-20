// module: mt7915.ko
// function: sta_ieee_802_3_data_tx @ 0x53044
// size: 28 bytes
//

void sta_ieee_802_3_data_tx(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined1 *)(param_3 + 0x35) = 0;
  *(undefined1 *)(param_3 + 0x34) = 0;
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  *(undefined1 *)(param_3 + 0x2c) = 0;
  return;
}

