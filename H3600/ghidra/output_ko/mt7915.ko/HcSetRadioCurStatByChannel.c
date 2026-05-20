// module: mt7915.ko
// function: HcSetRadioCurStatByChannel @ 0xa8d74
// size: 92 bytes
//

void HcSetRadioCurStatByChannel
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = RcGetHdevByChannel(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 0) {
    RcSetRadioCurStat(iVar1,param_3);
    return;
  }
  if (DebugLevel < 4) {
    return;
  }
  printk("%s(): no hdev parking on channel:%d !!!\n","HcSetRadioCurStatByChannel",param_2,param_4);
  return;
}

