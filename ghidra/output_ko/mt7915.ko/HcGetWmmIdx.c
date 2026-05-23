// module: mt7915.ko
// function: HcGetWmmIdx @ 0xa9c60
// size: 92 bytes
//

undefined4 HcGetWmmIdx(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 0xabc);
  iVar1 = hdev_obj_state_ready(uVar2);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","HcGetWmmIdx",*(undefined1 *)(param_2 + 0xc),
             DebugLevel,param_4);
    }
    return 0;
  }
  uVar2 = RcGetWmmIdx(uVar2);
  return uVar2;
}

