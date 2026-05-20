// module: mt7915.ko
// function: IsHcRadioCurStatOffByChannel @ 0xa8edc
// size: 108 bytes
//

bool IsHcRadioCurStatOffByChannel(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = RcGetHdevByChannel(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar1 != 0) {
    iVar1 = RcGetRadioCurStat();
    return iVar1 == 2;
  }
  if (DebugLevel < 4) {
    return true;
  }
  printk("%s(): no hdev parking on channel:%d!!!\n","IsHcRadioCurStatOffByChannel",param_2);
  return true;
}

