// module: mt7915.ko
// function: LoopBack_TxThread @ 0x28d994
// size: 636 bytes
//

undefined4 LoopBack_TxThread(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  iVar6 = *(int *)(param_1 + 0x10);
  if (2 < DebugLevel) {
    printk("%s, Repeat:%u\n","LoopBack_TxThread",*(undefined4 *)(iVar6 + 0xa3bb20),DebugLevel,
           param_4);
  }
  uVar1 = *(uint *)(iVar6 + 0xa3bb20);
  iVar4 = 0;
  uVar2 = 0;
  uVar5 = 0;
  if (uVar1 == 0) {
    uVar1 = 0xffffffff;
    *(undefined4 *)(iVar6 + 0xa3bb20) = 0xffffffff;
  }
  do {
    uVar3 = *(uint *)(iVar6 + 0xa3bb18);
    if (uVar1 == 0xffffffff) {
      uVar5 = 0;
    }
    if (uVar3 <= *(uint *)(iVar6 + 0xa3bb1c)) {
      do {
        while (*(char *)(iVar6 + 0xa3bafa) != '\0') {
          uVar2 = uVar2 + 1;
          RtmpusecDelay(0x32);
          if (2000 < uVar2) {
            if (-1 < DebugLevel) {
              printk("%s, no Rx come back  Stop1!!!\n","LoopBack_TxThread");
              goto LAB_0028dbb4;
            }
LAB_0028db48:
            LoopBack_Fail(iVar6,2);
            goto LAB_0028dae4;
          }
          if (-1 < DebugLevel) {
            printk("%s, no Rx BreakCount = %d\n","LoopBack_TxThread",uVar2);
          }
        }
        if (2000 < uVar2) {
LAB_0028dbb4:
          if (-1 < DebugLevel) {
            printk("%s, no Rx come back  Stop2!!!\n","LoopBack_TxThread");
          }
          goto LAB_0028db48;
        }
        if (-1 < DebugLevel) {
          printk("%s, Length =  %d\n","LoopBack_TxThread",uVar3,DebugLevel,param_4);
        }
        if (*(char *)(iVar6 + 0xa3baf9) == '\0') goto LAB_0028db14;
        if (*(int *)(iVar6 + 0xa3bafc) != 0) goto LAB_0028db0c;
        if (*(int *)(iVar6 + 0xa3bb24) == 0) {
          uVar3 = *(uint *)(iVar6 + 0xa59b50);
        }
        OS_SPIN_LOCK(iVar6 + 0xa77b58);
        *(undefined1 *)(iVar6 + 0xa3bafa) = 1;
        OS_SPIN_UNLOCK(iVar6 + 0xa77b58);
        if ((0xf000 < uVar3) && (2 < DebugLevel)) {
          printk("%s, LOOPBACK length too long\n","LoopBack_Run");
        }
        if (*(char *)(iVar6 + 0xa3baf9) == '\0') goto LAB_0028db14;
        if (*(int *)(iVar6 + 0xa3bafc) != 0) goto LAB_0028db0c;
        iVar4 = iVar4 + 1;
        RtmpusecDelay(200);
        if (-1 < DebugLevel) {
          printk("%s, DbgCount =  %d\n","LoopBack_TxThread",iVar4);
        }
        uVar2 = *(uint *)(iVar6 + 0xa3bb24);
        if (uVar2 == 0) break;
        uVar3 = uVar3 + 1;
        uVar2 = 0;
      } while (uVar3 <= *(uint *)(iVar6 + 0xa3bb1c));
    }
LAB_0028dae4:
    if (*(char *)(iVar6 + 0xa3baf9) == '\0') goto LAB_0028db14;
    if (*(int *)(iVar6 + 0xa3bafc) != 0) break;
    uVar1 = *(uint *)(iVar6 + 0xa3bb20);
    uVar5 = uVar5 + 1;
  } while (uVar5 < uVar1);
LAB_0028db0c:
  LoopBack_Stop(iVar6);
LAB_0028db14:
  if (3 < DebugLevel) {
    printk("+ + + + Control Thread Terminated + + + +\n");
  }
  RtmpOSTaskNotifyToExit(iVar6 + 0xa77b60);
  return 0;
}

