// module: mt7915.ko
// function: hc_check_ChCtrlChListStat @ 0xaab6c
// size: 20 bytes
//

bool hc_check_ChCtrlChListStat(int param_1,int param_2)

{
  return *(int *)(param_1 + 0x4dc) == param_2;
}

