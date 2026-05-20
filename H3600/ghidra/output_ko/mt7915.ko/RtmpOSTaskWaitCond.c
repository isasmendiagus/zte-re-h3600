// module: mt7915.ko
// function: RtmpOSTaskWaitCond @ 0x245614
// size: 4 bytes
//

bool RtmpOSTaskWaitCond(undefined4 param_1,int param_2,int param_3,int *param_4)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  undefined4 auStack_34 [3];
  undefined4 ***pppuStack_28;
  undefined4 ***pppuStack_24;
  
  if ((*(char *)(param_2 + 0x2c) == '\0') && (uVar4 = kthread_should_stop(), uVar4 < (param_3 == 0))
     ) {
    pppuStack_28 = &pppuStack_28;
    auStack_34[0] = 0;
    pppuStack_24 = pppuStack_28;
    while (iVar3 = prepare_to_wait_event(param_2 + 0x20,auStack_34,1),
          *(char *)(param_2 + 0x2c) == '\0') {
      bVar2 = kthread_should_stop();
      if (iVar3 != 0) {
        bVar2 = bVar2 | 1;
      }
      if (bVar2 != 0) break;
      schedule();
    }
    finish_wait(param_2 + 0x20,auStack_34);
  }
  *(undefined1 *)(param_2 + 0x2c) = 0;
  iVar3 = kthread_should_stop();
  if (iVar3 == 0) {
    *param_4 = 0;
  }
  else {
    *param_4 = -1;
  }
  if (*(char *)(param_2 + 0x18) == '\x01') {
    bVar1 = false;
  }
  else {
    bVar1 = *param_4 == 0;
  }
  return bVar1;
}

