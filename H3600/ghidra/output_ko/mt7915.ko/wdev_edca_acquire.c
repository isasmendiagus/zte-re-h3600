// module: mt7915.ko
// function: wdev_edca_acquire @ 0x14d2a8
// size: 112 bytes
//

undefined4 wdev_edca_acquire(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int extraout_r3;
  int iVar2;
  
  if (param_2 != 0) {
    if ((*(int *)(param_2 + 0x14) == 1) || (*(int *)(param_2 + 0x14) != 2)) {
      iVar2 = param_1 + (uint)*(byte *)(param_2 + 0x8d7) * 0x24;
      iVar1 = iVar2 + 0x795084;
    }
    else {
      iVar1 = GetStaCfgByWdev();
      iVar2 = extraout_r3;
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = iVar1 + 0x41e6;
      }
    }
    HcAcquiredEdca(param_1,param_2,iVar1,iVar2,param_4);
    return 1;
  }
  return 0;
}

