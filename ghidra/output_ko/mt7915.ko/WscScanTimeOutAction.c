// module: mt7915.ko
// function: WscScanTimeOutAction @ 0x1e7050
// size: 216 bytes
//

void WscScanTimeOutAction(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r1;
  undefined4 uVar1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r2;
  undefined4 uVar2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  int iVar3;
  
  if (param_2 == 0) {
    return;
  }
  iVar3 = *(int *)(param_2 + 0x29e8);
  if (iVar3 == 0) {
    return;
  }
  WscScanExec(iVar3);
  uVar1 = extraout_r1;
  uVar2 = extraout_r2;
  if (*(int *)(param_2 + 4) == 2) {
    if (((*(int *)(param_2 + 0x10) != 0) && (*(int *)(param_2 + 0x28e4) == 0)) &&
       (*(char *)(param_2 + 0x2c4d) != '\x01')) {
      RTMPSetTimer(param_2 + 0x2808,10000);
      *(undefined1 *)(param_2 + 0x2804) = 1;
      uVar1 = extraout_r1_01;
      uVar2 = extraout_r2_01;
    }
  }
  else if ((*(int *)(param_2 + 4) == 1) && (*(int *)(param_2 + 0x10) != 0)) {
    RTMPSetTimer(param_2 + 0x28ec,10000);
    *(undefined1 *)(param_2 + 0x28e8) = 1;
    uVar1 = extraout_r1_00;
    uVar2 = extraout_r2_00;
  }
  if (0 < DebugLevel) {
    printk("!!! WscScanTimeOutAction !!!\n");
    uVar1 = extraout_r1_02;
    uVar2 = extraout_r2_02;
  }
  RtmpOsMlmeUp(iVar3 + 0x286298,uVar1,uVar2,param_4);
  return;
}

