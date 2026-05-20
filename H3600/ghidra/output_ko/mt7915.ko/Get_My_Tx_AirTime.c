// module: mt7915.ko
// function: Get_My_Tx_AirTime @ 0xc841c
// size: 24 bytes
//

undefined4 Get_My_Tx_AirTime(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + (int)(&UNK_0029f0c6 + param_2) * 4 + 8);
}

