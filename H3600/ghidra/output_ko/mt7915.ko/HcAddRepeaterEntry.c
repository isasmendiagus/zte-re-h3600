// module: mt7915.ko
// function: HcAddRepeaterEntry @ 0xa90b4
// size: 116 bytes
//

undefined4 HcAddRepeaterEntry(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xabc);
  iVar1 = hdev_obj_state_ready(iVar2);
  if (iVar1 != 0) {
    OcAddRepeaterEntry(iVar2,*(undefined1 *)(param_1 + 0xe));
    RcUpdateRepeaterEntry(*(undefined4 *)(iVar2 + 8),*(undefined1 *)(param_1 + 0xe));
    return 0;
  }
  if (DebugLevel < 0) {
    return 1;
  }
  printk("%s(): wdev=%d, hobj is not ready!\n","HcAddRepeaterEntry",*(undefined1 *)(param_1 + 0xc),
         DebugLevel,param_4);
  return 1;
}

