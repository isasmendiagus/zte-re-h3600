// module: mt7915.ko
// function: mtf_rx_event_handler @ 0x1a0e54
// size: 116 bytes
//

void mtf_rx_event_handler(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = OS_TEST_BIT(0,param_1 + 0xa784a0);
  if (iVar1 == 0) {
    return;
  }
  iVar1 = AndesAllocCmdMsg(param_1,*(undefined2 *)(param_2 + 0x18));
  if (iVar1 == 0) {
    return;
  }
  AndesAppendCmdMsg(iVar1,param_2 + 0x18,*(undefined2 *)(param_2 + 0x18));
  AndesMTRxProcessEvent(param_1,iVar1);
  if (*(int *)(iVar1 + 0x20) != 0) {
    RTMPFreeNdisPacket(param_1);
  }
  AndesFreeCmdMsg(iVar1);
  return;
}

