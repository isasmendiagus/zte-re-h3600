// module: mt7915.ko
// function: hc_set_ChCtrlFlags_CAP @ 0xaa718
// size: 28 bytes
//

undefined4 hc_set_ChCtrlFlags_CAP(int param_1,uint param_2,int param_3)

{
  param_1 = param_1 + param_3 * 0x14;
  *(uint *)(param_1 + 0x10) = param_2 | *(uint *)(param_1 + 0x10);
  return 0;
}

