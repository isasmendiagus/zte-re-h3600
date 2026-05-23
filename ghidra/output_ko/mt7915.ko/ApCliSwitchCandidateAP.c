// module: mt7915.ko
// function: ApCliSwitchCandidateAP @ 0x6aa4c
// size: 656 bytes
//

void ApCliSwitchCandidateAP(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  uint uVar7;
  
  iVar4 = *param_1;
  iVar1 = get_scan_ctrl_by_wdev();
  if (*(char *)(iVar1 + 0x17c) != '\x01') {
    if (2 < DebugLevel) {
      printk("---> ApCliSwitchCandidateAP()\n");
    }
    if (param_2 != 0) {
      uVar3 = (uint)*(byte *)(param_2 + 0xe);
      if (uVar3 < 2) {
        if (*(char *)((int)param_1 + uVar3 * 0x2137b0 + 0x580eae) == '\x01') {
          piVar6 = param_1 + uVar3 * 0x84dec + 0xdc760;
          if (*piVar6 == 0) {
            if (2 < DebugLevel) {
              printk("No Bss\n");
            }
            *(undefined1 *)(param_1 + uVar3 * 0x84dec + 0x1603ba) = 0;
          }
          else {
            iVar1 = *piVar6 + -1;
            *piVar6 = iVar1;
            __memzero(param_1 + uVar3 * 0x84dec + iVar1 * 0x2bd + 0xdc762,0xaf4);
            uVar7 = *piVar6 - 1;
            if (uVar7 < 0xff) {
              iVar1 = ApCliAutoConnectBWAdjust
                                (param_1,param_2,param_1 + uVar3 * 0x84dec + uVar7 * 0x2bd + 0xdc762
                                );
              if (iVar1 != 0) {
                if (2 < DebugLevel) {
                  printk("Switch to channel :%d\n",
                         (&DAT_00371d94)[(int)(param_1 + uVar7 * 0x2bd + uVar3 * 0x84dec)]);
                }
                rtmp_set_channel(param_1,param_2,
                                 (&DAT_00371d94)[(int)(param_1 + uVar3 * 0x84dec + uVar7 * 0x2bd)]);
              }
            }
            else {
              if (2 < DebugLevel) {
                printk("No candidate AP, the process is about to stop.\n");
              }
              *(undefined1 *)(param_1 + uVar3 * 0x84dec + 0x1603ba) = 0;
            }
            RtmpOSNetDevProtect(1);
            uVar5 = *(undefined4 *)(iVar4 + 0x3c);
            uVar2 = *(undefined4 *)(iVar4 + 0x38);
            *(undefined4 *)(iVar4 + 0x38) = 0x400;
            *(uint *)(iVar4 + 0x3c) = uVar3;
            Set_ApCli_Enable_Proc(param_1,&_LC55);
            *(undefined4 *)(iVar4 + 0x3c) = uVar5;
            *(undefined4 *)(iVar4 + 0x38) = uVar2;
            RtmpOSNetDevProtect(0);
            if (2 < DebugLevel) {
              printk("---> ApCliSwitchCandidateAP()\n");
              return;
            }
          }
        }
      }
      else if (-1 < DebugLevel) {
        printk("Error  ifIdx=%d\n",uVar3);
        return;
      }
    }
  }
  return;
}

