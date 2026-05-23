// module: tm.ko
// function: opcDbCmdEntryValidSet @ 0x557f8
// size: 236 bytes
//

undefined4 opcDbCmdEntryValidSet(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int *piVar2;
  short sVar3;
  int *piVar4;
  undefined4 *puVar5;
  
  piVar4 = s_tmCmdInfoListHead;
  if (param_1 != 0) {
    while (piVar1 = piVar4 + 4, param_1 != *piVar1) {
      piVar4 = (int *)piVar4[1];
      if (piVar4 == (int *)0x0) {
        printk("ERROR:the index %d of cmd entry isnot exist",param_1,*piVar1,0,param_4);
        return 0;
      }
    }
    if (param_2 != 0) {
      *(undefined1 *)(piVar4 + 5) = 1;
      *(short *)((int)piVar4 + 0x16) = *(short *)((int)piVar4 + 0x16) + 1;
      return 0;
    }
    sVar3 = *(short *)((int)piVar4 + 0x16) + -1;
    *(short *)((int)piVar4 + 0x16) = sVar3;
    if (sVar3 == 0) {
      puVar5 = (undefined4 *)piVar4[1];
      *(undefined1 *)(piVar4 + 5) = 0;
      if ((puVar5 != (undefined4 *)0x0) && (l_cmdAllAlloc != '\0')) {
        if (*piVar4 == 0) {
          *puVar5 = 0;
          s_tmCmdInfoListHead = (int *)piVar4[1];
        }
        else {
          *(undefined4 **)(*piVar4 + 4) = puVar5;
          *(int *)piVar4[1] = *piVar4;
        }
        piVar1 = s_tmCmdInfoListTail;
        piVar4[1] = 0;
        piVar2 = piVar4;
        *piVar4 = (int)s_tmCmdInfoListTail;
        s_tmCmdInfoListTail = piVar2;
        piVar1[1] = (int)piVar4;
      }
    }
  }
  return 0;
}

