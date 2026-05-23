// module: mt7915.ko
// function: Get_My_Rx_AirTime @ 0xc8434
// size: 24 bytes
//

undefined4 Get_My_Rx_AirTime(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + (int)("cmd_txbf_en_dynsnd_intr" + param_2) * 4 + 8);
}

