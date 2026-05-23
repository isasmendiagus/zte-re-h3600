// module: mt7915.ko
// function: HcGetOmacIdx @ 0xa9870
// size: 92 bytes
//

undefined1 HcGetOmacIdx(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 0xabc);
  iVar1 = hdev_obj_state_ready(iVar2);
  if (iVar1 != 0) {
    return *(undefined1 *)(iVar2 + 4);
  }
  if (DebugLevel < 0) {
    return 0xff;
  }
  printk("%s(): wdev=%d, hobj is not ready!\n","HcGetOmacIdx",*(undefined1 *)(param_2 + 0xc),
         DebugLevel,param_4);
  return 0xff;
}

