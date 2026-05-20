// module: tm.ko
// function: opcDbFlowEntryValidSet @ 0x578c8
// size: 384 bytes
//

undefined4 opcDbFlowEntryValidSet(int param_1,int param_2)

{
  short sVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  short *psVar8;
  
  piVar7 = s_tmFlowInfoListHead;
  do {
    psVar8 = (short *)piVar7[4];
    if (*(int *)(psVar8 + 2) == param_1) {
      if (param_2 == 0) {
        hw_watchdog_reset();
        sVar1 = *psVar8;
        *psVar8 = sVar1 + -1;
        if ((short)(sVar1 + -1) == 0) {
          __memzero(piVar7[4],0x28);
          piVar2 = s_tmFlowInfoListHead_u;
          piVar5 = s_tmFlowInfoListHead;
          *(undefined1 *)(piVar7[4] + 8) = 0;
          piVar6 = (int *)&s_tmFlowInfoListHead;
          *(undefined1 *)(piVar7 + 2) = 0;
          *(int *)(piVar7[4] + 4) = param_1;
          *(undefined2 *)(piVar7[4] + 0x1a) = 0xffff;
          *(undefined2 *)(piVar7[4] + 0x14) = 0xffff;
          puVar3 = (undefined4 *)piVar7[1];
          if (piVar5 == piVar2) {
            if ((puVar3 != (undefined4 *)0x0) && (l_flowAllAlloc_u != '\0')) {
              if (*piVar7 == 0) {
                *puVar3 = 0;
                piVar5 = (int *)piVar7[1];
                s_tmFlowInfoListHead_u = piVar5;
              }
              else {
                *(undefined4 **)(*piVar7 + 4) = puVar3;
                piVar5 = (int *)*piVar7;
                piVar6 = (int *)piVar7[1];
              }
              *piVar6 = (int)piVar5;
              piVar6 = s_tmFlowInfoListTail_u;
              piVar7[1] = 0;
              piVar5 = piVar7;
              *piVar7 = (int)s_tmFlowInfoListTail_u;
              s_tmFlowInfoListTail_u = piVar5;
              piVar6[1] = (int)piVar7;
            }
          }
          else if ((puVar3 != (undefined4 *)0x0) && (l_flowAllAlloc_d != '\0')) {
            if (*piVar7 == 0) {
              *puVar3 = 0;
              iVar4 = piVar7[1];
              s_tmFlowInfoListHead_d = iVar4;
            }
            else {
              *(undefined4 **)(*piVar7 + 4) = puVar3;
              iVar4 = *piVar7;
              piVar6 = (int *)piVar7[1];
            }
            *piVar6 = iVar4;
            piVar6 = s_tmFlowInfoListTail_d;
            piVar7[1] = 0;
            piVar5 = piVar7;
            *piVar7 = (int)s_tmFlowInfoListTail_d;
            s_tmFlowInfoListTail_d = piVar5;
            piVar6[1] = (int)piVar7;
          }
        }
      }
      else {
        *(undefined1 *)(piVar7 + 2) = 1;
        *psVar8 = *psVar8 + 1;
      }
      return 0;
    }
    piVar7 = (int *)piVar7[1];
  } while (piVar7 != (int *)0x0);
  printk("ERROR:the index %d of flow entry isnot exist",param_1);
  return 0;
}

