// module: mt7915.ko
// function: hc_set_ChCtrlChListStat @ 0xaa734
// size: 12 bytes
//

undefined4 hc_set_ChCtrlChListStat(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x4dc) = param_2;
  return 0;
}

