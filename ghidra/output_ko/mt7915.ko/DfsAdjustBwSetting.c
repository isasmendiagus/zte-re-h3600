// module: mt7915.ko
// function: DfsAdjustBwSetting @ 0x2346d8
// size: 80 bytes
//

void DfsAdjustBwSetting(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xb10);
  if (param_3 == param_2) {
    return;
  }
  switch(param_3) {
  case 0:
    uVar2 = 0;
    uVar1 = 0;
    break;
  case 1:
    uVar2 = 0;
    uVar1 = 1;
    break;
  case 2:
    uVar2 = 1;
    uVar1 = 1;
    break;
  case 3:
    uVar2 = 2;
    uVar1 = 1;
    break;
  default:
    goto switchD_002346e8_default;
  }
  *(undefined1 *)(iVar3 + 0x15) = uVar1;
  *(undefined1 *)(iVar3 + 0x5c) = uVar2;
switchD_002346e8_default:
  return;
}

