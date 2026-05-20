// module: mt7915.ko
// function: sta_wait_link_down @ 0x689bc
// size: 116 bytes
//

void sta_wait_link_down(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = RTMPMsecsToJiffies(500);
  iVar2 = wait_for_completion_timeout(param_1 + 0x213244,uVar1);
  if (iVar2 != 0) {
    return;
  }
  uVar1 = *(undefined4 *)(param_1 + 8);
  if (-1 < DebugLevel) {
    printk("(%s) sta idx [%d] can\'t linkdown within 500ms, do linkdown in main thread\n",
           "sta_wait_link_down",*(undefined1 *)(param_1 + 0xe));
  }
  LinkDown(uVar1,0,param_1,0);
  return;
}

