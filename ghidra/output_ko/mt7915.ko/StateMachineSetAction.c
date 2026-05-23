// module: mt7915.ko
// function: StateMachineSetAction @ 0x12ebe4
// size: 48 bytes
//

void StateMachineSetAction(int *param_1,uint param_2,int param_3,undefined4 param_4)

{
  if (param_2 < (uint)param_1[1]) {
    if ((uint)(param_3 - *param_1) < (uint)param_1[2]) {
      *(undefined4 *)(param_1[4] + (param_1[2] * param_2 + (param_3 - *param_1)) * 4) = param_4;
    }
    return;
  }
  return;
}

