// module: mt7915.ko
// function: RadarStateCheck @ 0x100c64
// size: 404 bytes
//

void RadarStateCheck(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  undefined1 uVar3;
  int iVar4;
  
  if (param_2 == 0) {
    return;
  }
  iVar4 = *(int *)(param_2 + 0x3fe4);
  if (iVar4 == 0) {
    return;
  }
  iVar2 = *(int *)(param_2 + 0xb10);
  if (iVar2 == 0) {
    return;
  }
  if (*(char *)(iVar2 + 0x15) == '\x01') {
    cVar1 = *(char *)(iVar2 + 0x5c);
    uVar3 = 1;
    if (cVar1 != '\0') {
      if (cVar1 == '\x01') {
        uVar3 = 2;
      }
      else if (cVar1 == '\x02') {
        uVar3 = 3;
      }
      else if (cVar1 == '\x03') {
        uVar3 = 6;
      }
      else {
        uVar3 = 0;
      }
    }
  }
  else {
    uVar3 = 0;
  }
  if (*(char *)(param_2 + 0x944) != '\0') {
    return;
  }
  if ((*(char *)(param_1 + 0x795074) == '\x01') &&
     (iVar2 = DfsRadarChannelCheck(param_1,param_2,*(undefined1 *)(iVar2 + 5),uVar3,param_4),
     iVar2 != 0)) {
    if (0 < DebugLevel) {
      printk(&_LC1,"RadarStateCheck");
    }
    *(undefined1 *)(iVar4 + 4) = 2;
    *(undefined2 *)(iVar4 + 2) = 0;
    *(undefined4 *)(iVar4 + 0x10) = 0;
    iVar2 = DfsIsOutBandAvailable(param_1,param_2);
    if (iVar2 == 0) {
      iVar2 = DfsIsTargetChAvailable(param_1);
      if (iVar2 == 0) {
        return;
      }
      if (0 < DebugLevel) {
        printk(&_LC3,"RadarStateCheck");
      }
    }
    else if (0 < DebugLevel) {
      printk(&_LC2,"RadarStateCheck");
    }
  }
  else if (((*(ushort *)(param_2 + 0x18) & 0xb1) != 0) && (0 < DebugLevel)) {
    printk(&_LC4,"RadarStateCheck");
  }
  *(undefined1 *)(iVar4 + 4) = 0;
  return;
}

