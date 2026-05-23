// module: mt7915.ko
// function: sys_ad_wait_os_task @ 0x25ed54
// size: 4 bytes
//

bool sys_ad_wait_os_task(undefined4 param_1,int param_2,int *param_3)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  undefined4 auStack_2c [3];
  undefined4 ***pppuStack_20;
  undefined4 ***pppuStack_1c;
  
  if ((*(char *)(param_2 + 0x2c) == '\0') && (iVar3 = kthread_should_stop(), iVar3 == 0)) {
    pppuStack_20 = &pppuStack_20;
    auStack_2c[0] = 0;
    pppuStack_1c = pppuStack_20;
    while (iVar3 = prepare_to_wait_event(param_2 + 0x20,auStack_2c,1),
          *(char *)(param_2 + 0x2c) == '\0') {
      bVar2 = kthread_should_stop();
      if (iVar3 != 0) {
        bVar2 = bVar2 | 1;
      }
      if (bVar2 != 0) break;
      schedule();
    }
    finish_wait(param_2 + 0x20,auStack_2c);
  }
  *(undefined1 *)(param_2 + 0x2c) = 0;
  iVar3 = kthread_should_stop();
  if (iVar3 == 0) {
    *param_3 = 0;
  }
  else {
    *param_3 = -1;
  }
  if (*(char *)(param_2 + 0x18) == '\x01') {
    bVar1 = false;
  }
  else {
    bVar1 = *param_3 == 0;
  }
  return bVar1;
}

