// module: mt7915.ko
// function: HwCtrlExit @ 0xb24b4
// size: 84 bytes
//

void HwCtrlExit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r1;
  
  FUN_000b1f24();
  RtmpOSTaskKill(param_1 + 0x285cac);
  *(undefined4 *)(param_1 + 0x285ce0) = 0;
  *(undefined4 *)(param_1 + 0x285ce4) = 0;
  *(undefined4 *)(param_1 + 0x285ce8) = 0;
  *(undefined4 *)(param_1 + 0x285cec) = 0;
  *(undefined4 *)(param_1 + 0x285cf0) = 0;
  *(undefined4 *)(param_1 + 0x285cf4) = 0;
  *(undefined4 *)(param_1 + 0x285cf8) = 0;
  RtmpOSTaskKill(param_1 + 0x285cfc,extraout_r1,0,param_4);
  return;
}

