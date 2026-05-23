// module: mt7915.ko
// function: Get_EDCCA_Time @ 0xc844c
// size: 24 bytes
//

undefined4 Get_EDCCA_Time(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + (int)("cmd_txbf_en_dynsnd_intr" + param_2 + 2) * 4 + 8);
}

