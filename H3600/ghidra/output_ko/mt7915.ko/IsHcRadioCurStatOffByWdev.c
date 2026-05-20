// module: mt7915.ko
// function: IsHcRadioCurStatOffByWdev @ 0xa8e6c
// size: 108 bytes
//

bool IsHcRadioCurStatOffByWdev(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xabc);
  iVar1 = hdev_obj_state_ready(iVar2);
  if (iVar1 != 0) {
    iVar1 = RcGetRadioCurStat(*(undefined4 *)(iVar2 + 8));
    return iVar1 == 2;
  }
  if (DebugLevel < 3) {
    return true;
  }
  printk("%s(): wdev_idx %d obj is not ready, return TRUE !!!\n","IsHcRadioCurStatOffByWdev",
         *(undefined1 *)(param_1 + 0xc),DebugLevel,param_4);
  return true;
}

