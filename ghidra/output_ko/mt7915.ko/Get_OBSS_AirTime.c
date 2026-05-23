// module: mt7915.ko
// function: Get_OBSS_AirTime @ 0xc83b4
// size: 24 bytes
//

undefined4 Get_OBSS_AirTime(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + (int)("CmdTxBfAwareCtrl" + param_2 + 0x10) * 4 + 8);
}

