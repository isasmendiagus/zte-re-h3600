// module: mt7915.ko
// function: RtmpOsPktInit @ 0x243aa0
// size: 24 bytes
//

void RtmpOsPktInit(int param_1,undefined4 param_2,int param_3,int param_4)

{
  *(int *)(param_1 + 0xcc) = param_3;
  *(undefined4 *)(param_1 + 0x18) = param_2;
  *(int *)(param_1 + 100) = param_4;
  *(int *)(param_1 + 0xc0) = param_3 + param_4;
  return;
}

