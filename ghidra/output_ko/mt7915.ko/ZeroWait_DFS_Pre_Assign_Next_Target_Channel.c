// module: mt7915.ko
// function: ZeroWait_DFS_Pre_Assign_Next_Target_Channel @ 0x237e88
// size: 28 bytes
//

void ZeroWait_DFS_Pre_Assign_Next_Target_Channel
               (int param_1,undefined1 param_2,undefined1 param_3,undefined2 param_4)

{
  *(undefined1 *)(param_1 + 0x7953f1) = param_2;
  *(undefined1 *)(param_1 + 0x7953f2) = param_3;
  *(undefined2 *)(param_1 + 0x7953f4) = param_4;
  return;
}

