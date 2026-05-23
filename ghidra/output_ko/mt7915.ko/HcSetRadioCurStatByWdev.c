// module: mt7915.ko
// function: HcSetRadioCurStatByWdev @ 0xa8cc4
// size: 84 bytes
//

void HcSetRadioCurStatByWdev(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xabc);
  iVar1 = hdev_obj_state_ready(iVar2);
  if (iVar1 != 0) {
    RcSetRadioCurStat(*(undefined4 *)(iVar2 + 8),param_2,extraout_r2,param_4);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s(): obj is not ready!!\n","HcSetRadioCurStatByWdev",extraout_r2,param_4);
  return;
}

