// module: mt7915.ko
// function: twtPlannerRxNegoResult @ 0x16a088
// size: 572 bytes
//

void twtPlannerRxNegoResult(int param_1,int param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      pcVar2 = "%s: wdev=NULL, please check\n";
LAB_0016a268:
      printk(pcVar2,"twtPlannerRxNegoResult");
      return;
    }
  }
  else {
    uVar3 = (uint)*(byte *)(param_2 + 0xe);
    iVar1 = uVar3 * 0x2137b0;
    if (&DAT_0036db58 + param_1 + iVar1 == (undefined *)0x0) {
      if (-1 < DebugLevel) {
        pcVar2 = "%s: apcli_entry=NULL, please check\n";
        goto LAB_0016a268;
      }
    }
    else {
      iVar7 = *(int *)(&DAT_0057ffc4 + param_1 + iVar1);
      if (iVar7 == 0) {
        if (-1 < DebugLevel) {
          pcVar2 = "%s: pEntry=NULL, please check\n";
          goto LAB_0016a268;
        }
      }
      else {
        puVar4 = (undefined4 *)(param_1 + iVar1 + param_3 * 0x38 + 0x580f58);
        if (2 < DebugLevel) {
          printk("%s: ucSetupCmd=%d\n","twtPlannerRxNegoResult",
                 (&DAT_00580f5c)[param_1 + param_3 * 0x38 + uVar3 * 0x2137b0]);
        }
        switch((&DAT_00580f5c)[param_1 + uVar3 * 0x2137b0 + param_3 * 0x38]) {
        case 4:
          twtPlannerAddAgrtTbl(param_1,param_2,iVar7,puVar4,param_3);
          break;
        case 5:
        case 6:
          uVar8 = puVar4[1];
          uVar5 = puVar4[2];
          uVar6 = puVar4[3];
          iVar7 = uVar3 * 0x2137b0 + param_3 * 0x38;
          iVar1 = param_1 + iVar7;
          *(undefined4 *)(&DAT_00580f40 + param_1 + iVar7) = *puVar4;
          *(undefined4 *)(&DAT_00580f40 + iVar1 + 4) = uVar8;
          *(undefined4 *)(&DAT_00580f40 + iVar1 + 8) = uVar5;
          *(undefined4 *)(&DAT_00580f40 + iVar1 + 0xc) = uVar6;
          uVar5 = puVar4[5];
          *(undefined4 *)(&DAT_00580f40 + iVar1 + 0x10) = puVar4[4];
          *(undefined4 *)(&DAT_00580f40 + iVar1 + 0x14) = uVar5;
          (&DAT_00580f44)[param_1 + iVar7] = 1;
          (&DAT_00580f40)[param_1 + iVar7] = 1;
          twtReqFsmSendEvent(param_1,param_2,param_3,0);
          return;
        case 7:
          break;
        default:
          printk(&_LC50,0x808);
          dump_stack();
          return;
        }
      }
    }
  }
  return;
}

