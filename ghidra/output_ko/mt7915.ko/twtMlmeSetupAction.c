// module: mt7915.ko
// function: twtMlmeSetupAction @ 0x16a644
// size: 284 bytes
//

void twtMlmeSetupAction(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_2 + 1);
  uVar1 = param_2[5];
  uVar2 = *param_2;
  if ((iVar4 != 0) &&
     (iVar3 = FUN_001675e4(&DAT_0036db58 + param_1 + (uint)*(byte *)(iVar4 + 0xe) * 0x2137b0,uVar1),
     iVar3 != 0)) {
    switch(uVar2) {
    case 0:
      twtReqFsmSteps(param_1,iVar4,1,uVar1,iVar3);
      return;
    case 1:
      twtReqFsmSteps(param_1,iVar4,6,uVar1,iVar3);
      return;
    case 4:
      twtPlannerRxNegoResult(param_1,iVar4,uVar1);
      return;
    case 7:
      twtPlannerTeardownDone(param_1,iVar4,uVar1);
      return;
    case 9:
      twtPlannerSetParams(param_1,iVar4,*(undefined4 *)(param_2 + 6),*(undefined4 *)(param_2 + 10),
                          *(undefined4 *)(param_2 + 0xe),*(undefined4 *)(param_2 + 0x12),
                          *(undefined4 *)(param_2 + 0x16),*(undefined4 *)(param_2 + 0x1a),
                          *(undefined4 *)(param_2 + 0x1e),*(undefined4 *)(param_2 + 0x22));
    }
  }
  return;
}

