// module: mt7915.ko
// function: StateMachineInit @ 0x12eb70
// size: 116 bytes
//

void StateMachineInit(undefined4 *param_1,undefined4 param_2,int param_3,int param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  param_1[1] = param_3;
  param_1[4] = param_2;
  param_1[2] = param_4;
  *param_1 = param_7;
  if (param_3 != 0) {
    iVar3 = 0;
    iVar2 = 0;
    do {
      if (param_4 != 0) {
        iVar1 = 0;
        iVar4 = iVar3;
        do {
          iVar1 = iVar1 + 1;
          *(undefined4 *)(param_1[4] + iVar4) = param_5;
          iVar4 = iVar4 + 4;
        } while (iVar1 != param_4);
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + param_4 * 4;
    } while (iVar2 != param_3);
  }
  param_1[3] = param_6;
  return;
}

