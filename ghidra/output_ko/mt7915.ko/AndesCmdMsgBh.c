// module: mt7915.ko
// function: AndesCmdMsgBh @ 0x1a4984
// size: 196 bytes
//

void AndesCmdMsgBh(int param_1)

{
  int iVar1;
  uint uVar2;
  
  while (iVar1 = AndesDequeueCmdMsg(param_1 + 0xa7849c,param_1 + 0xa784f8), iVar1 != 0) {
    hif_rx_event_process(param_1,iVar1);
    AndesFreeCmdMsg(iVar1);
  }
  while (iVar1 = AndesDequeueCmdMsg(param_1 + 0xa7849c,param_1 + 0xa784ec), iVar1 != 0) {
    uVar2 = *(uint *)(iVar1 + 0x18);
    if (((uVar2 < 2) || ((3 < uVar2 && (uVar2 != 5)))) && (-1 < DebugLevel)) {
      printk("unknow msg state(%d)\n");
    }
    AndesFreeCmdMsg(iVar1);
  }
  iVar1 = OS_TEST_BIT(0,param_1 + 0xa784a0);
  if (iVar1 == 0) {
    return;
  }
  AndesBhSchedule(param_1);
  return;
}

