// module: mt7915.ko
// function: HcGetBcnQueueIdx @ 0xa9c00
// size: 92 bytes
//

undefined4 HcGetBcnQueueIdx(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 0xabc);
  iVar1 = hdev_obj_state_ready(uVar2);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","HcGetBcnQueueIdx",*(undefined1 *)(param_2 + 0xc)
             ,DebugLevel,param_4);
    }
    return 0x12;
  }
  uVar2 = RcGetBcnQueueIdx(uVar2);
  return uVar2;
}

