// module: mt7915.ko
// function: HwCtrlSetPbc @ 0xaeb60
// size: 44 bytes
//

void HwCtrlSetPbc(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_2 + 8);
  if (*piVar3 == 0) {
    uVar1 = 0xff;
  }
  else {
    uVar1 = *(undefined1 *)(*piVar3 + 0x999);
  }
  if (piVar3[1] == 0) {
    uVar2 = 0xffff;
  }
  else {
    uVar2 = *(undefined2 *)(piVar3[1] + 0xe0);
  }
  MtCmdPktBudgetCtrl(param_1,uVar1,uVar2,(char)piVar3[2]);
  return;
}

