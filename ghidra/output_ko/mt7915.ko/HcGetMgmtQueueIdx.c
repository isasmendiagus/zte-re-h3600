// module: mt7915.ko
// function: HcGetMgmtQueueIdx @ 0xa9b98
// size: 100 bytes
//

undefined4 HcGetMgmtQueueIdx(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 0xabc);
  iVar1 = hdev_obj_state_ready(uVar2);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","HcGetMgmtQueueIdx",
             *(undefined1 *)(param_2 + 0xc));
    }
    return 0x10;
  }
  uVar2 = RcGetMgmtQueueIdx(uVar2,param_3);
  return uVar2;
}

