// module: mt7915.ko
// function: twtReqFsmSteps @ 0x1691f8
// size: 400 bytes
//

void twtReqFsmSteps(int param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  
  iVar1 = DebugLevel;
  if (param_2 == 0) {
switchD_00169258_caseD_2:
    return;
  }
  uVar4 = (uint)*(byte *)(param_2 + 0xe);
  iVar2 = param_1 + uVar4 * 0x2137b0;
  iVar5 = *(int *)(&DAT_00580f3c + iVar2);
  *(undefined4 *)(&DAT_00580f3c + iVar2) = param_3;
  if (2 < iVar1) goto LAB_00169374;
  do {
    switch(param_3) {
    case 0:
switchD_00169258_caseD_0:
      if (iVar5 == 2) {
        uVar3 = 4;
      }
      else {
        if (iVar5 == 6) {
switchD_00169258_caseD_7:
          twtReqFsmSendEvent(param_1,param_2,param_4,7);
          return;
        }
        if (iVar5 != 5) {
          return;
        }
        uVar3 = 6;
      }
      twtReqFsmSendEvent(param_1,param_2,param_4,uVar3);
      return;
    case 1:
      if (param_5 == 0) {
        printk(&_LC29,0x853);
        dump_stack();
      }
      iVar2 = twtSendSetupFrame(param_1,param_2,param_4,param_5);
      iVar1 = DebugLevel;
      break;
    default:
      goto switchD_00169258_caseD_2;
    case 6:
      iVar2 = twtSendTeardownFrame(param_1,param_2,param_4);
      iVar1 = DebugLevel;
      break;
    case 7:
      goto switchD_00169258_caseD_7;
    }
    if (iVar2 == 0) {
      DebugLevel = iVar1;
      return;
    }
    param_3 = 0;
    iVar2 = param_1 + uVar4 * 0x2137b0;
    iVar5 = *(int *)(&DAT_00580f3c + iVar2);
    DebugLevel = iVar1;
    *(undefined4 *)(&DAT_00580f3c + iVar2) = 0;
    if (iVar1 < 3) goto switchD_00169258_caseD_0;
LAB_00169374:
    printk("twtReqFsmSteps ePreState=%d, eNextState=%d\n",iVar5,param_3);
    param_3 = *(undefined4 *)(&DAT_00580f3c + param_1 + uVar4 * 0x2137b0);
  } while( true );
}

