// module: mt7915.ko
// function: setVHTETxBFCap @ 0x173ed0
// size: 592 bytes
//

void setVHTETxBFCap(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(param_2 + 0x28);
  iVar4 = *(int *)(param_2 + 0x18);
  if (iVar3 == 0) {
    *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xe0;
    *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) & 7;
    return;
  }
  if (iVar3 == 2) {
    *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) & 0xef;
    bVar2 = *(byte *)(iVar4 + 1) & 0xf7 | (1 < *(byte *)(param_2 + 4)) << 3;
    *(byte *)(iVar4 + 1) = bVar2;
    switch(*(undefined4 *)(param_1 + 0x7959a0)) {
    case 0:
    case 2:
      *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xe7;
      break;
    case 1:
    case 3:
      *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xef;
      *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xf7 | (1 < *(byte *)(param_2 + 4)) << 3;
      break;
    default:
      if (-1 < DebugLevel) {
        printk("%s: set wrong parameters\n","setVHTETxBFCap",bVar2,DebugLevel,param_4);
      }
    }
    *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) & 0x1f;
    *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xf8 | *(char *)(param_2 + 4) - 1U & 7;
    return;
  }
  if (iVar3 == 3) {
    *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) & 0xf7 | 0x10;
    switch(*(undefined4 *)(param_1 + 0x7959a0)) {
    case 0:
    case 1:
      goto switchD_00173f18_caseD_0;
    case 2:
    case 3:
switchD_00173f18_caseD_2:
      *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xf7 | 0x10;
      goto LAB_0017400c;
    default:
switchD_00173f18_default:
      if (-1 < DebugLevel) {
        printk("%s: set wrong parameters\n","setVHTETxBFCap",param_3,DebugLevel,param_4);
      }
      goto LAB_0017400c;
    }
  }
  *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) | 0x10;
  param_3 = *(byte *)(iVar4 + 1) & 0xfffffff7 | (uint)(1 < *(byte *)(param_2 + 4)) << 3;
  *(char *)(iVar4 + 1) = (char)param_3;
  switch(*(undefined4 *)(param_1 + 0x7959a0)) {
  case 0:
    goto switchD_00173f18_caseD_0;
  case 1:
    bVar2 = *(byte *)(iVar4 + 2) & 0xef;
    break;
  case 2:
    goto switchD_00173f18_caseD_2;
  case 3:
    bVar2 = *(byte *)(iVar4 + 2) | 0x10;
    break;
  default:
    goto switchD_00173f18_default;
  }
  *(byte *)(iVar4 + 2) = bVar2;
  *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xf7 | (1 < *(byte *)(param_2 + 4)) << 3;
LAB_0017400c:
  bVar2 = *(byte *)(iVar4 + 1);
  if ((bVar2 & 0xe0) == 0) {
    *(byte *)(iVar4 + 1) = bVar2 & 0x1f | 0x60;
  }
  else {
    bVar1 = bVar2 >> 5;
    if (2 < bVar1) {
      bVar1 = 3;
    }
    *(byte *)(iVar4 + 1) = bVar2 & 0x1f | bVar1 << 5;
  }
  *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xf8 | *(char *)(param_2 + 4) - 1U & 7;
  return;
switchD_00173f18_caseD_0:
  *(byte *)(iVar4 + 2) = *(byte *)(iVar4 + 2) & 0xe7;
  goto LAB_0017400c;
}

