// module: mt7915.ko
// function: AndesMTRxEventHandler @ 0x1ab328
// size: 120 bytes
//

void AndesMTRxEventHandler(int param_1,undefined2 *param_2)

{
  int iVar1;
  
  iVar1 = OS_TEST_BIT(0,param_1 + 0xa784a0);
  if (iVar1 == 0) {
    return;
  }
  iVar1 = AndesAllocCmdMsg(param_1,*param_2);
  if (iVar1 == 0) {
    return;
  }
  if (*(int *)(iVar1 + 0x20) == 0) {
    return;
  }
  AndesAppendCmdMsg(iVar1,param_2,*param_2);
  AndesMTRxProcessEvent(param_1,iVar1);
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(iVar1 + 0x20));
  AndesFreeCmdMsg(iVar1);
  return;
}

