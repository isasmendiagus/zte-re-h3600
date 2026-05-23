// module: mt7915.ko
// function: RtmpOSTaskAttach @ 0x245498
// size: 260 bytes
//

undefined4 RtmpOSTaskAttach(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  *(undefined1 *)(param_1 + 0x18) = 0;
  if (*(int *)(param_1 + 0x1c) == 0) {
    uVar1 = kthread_create_on_node(param_2,param_3,0,param_1);
    *(uint *)(param_1 + 0x1c) = uVar1;
    if (uVar1 < 0xfffff001) {
      kthread_bind(uVar1,0);
      wake_up_process(*(undefined4 *)(param_1 + 0x1c));
      uVar3 = 0;
      iVar2 = DebugLevel;
    }
    else {
      if (-1 < DebugLevel) {
        printk("%s kthread_run %s err %ld\n","__RtmpOSTaskAttach",param_1,uVar1);
      }
      iVar2 = DebugLevel;
      uVar3 = 1;
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
  }
  else {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s non-null kthread_task %s\n","__RtmpOSTaskAttach",param_1);
    uVar3 = 1;
    iVar2 = DebugLevel;
  }
  if (2 < iVar2) {
    printk("%s %s end %d\n","__RtmpOSTaskAttach",param_1,uVar3);
  }
  return uVar3;
}

