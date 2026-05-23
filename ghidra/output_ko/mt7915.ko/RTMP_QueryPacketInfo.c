// module: mt7915.ko
// function: RTMP_QueryPacketInfo @ 0x243644
// size: 52 bytes
//

void RTMP_QueryPacketInfo(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  param_2[1] = 1;
  uVar1 = *(undefined4 *)(param_1 + 0xcc);
  *param_2 = 1;
  param_2[3] = uVar1;
  param_2[2] = *(undefined4 *)(param_1 + 100);
  *param_3 = *(undefined4 *)(param_1 + 0xcc);
  *param_4 = *(undefined4 *)(param_1 + 100);
  return;
}

