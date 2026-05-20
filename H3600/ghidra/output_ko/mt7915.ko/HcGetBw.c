// module: mt7915.ko
// function: HcGetBw @ 0xa9b38
// size: 92 bytes
//

undefined4 HcGetBw(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_2 + 0xabc);
  iVar1 = hdev_obj_state_ready(iVar3);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","HcGetBw",*(undefined1 *)(param_2 + 0xc),
             DebugLevel,param_4);
    }
    return 0xff;
  }
  uVar2 = RcGetBw(*(undefined4 *)(iVar3 + 8));
  return uVar2;
}

