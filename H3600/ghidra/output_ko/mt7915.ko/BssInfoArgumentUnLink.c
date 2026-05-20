// module: mt7915.ko
// function: BssInfoArgumentUnLink @ 0x14db4c
// size: 96 bytes
//

void BssInfoArgumentUnLink(undefined4 param_1,int param_2)

{
  ReleaseBssIdx(param_1,*(undefined1 *)(param_2 + 0x999));
  HcReleaseGroupKeyWcid(param_1,param_2,*(undefined2 *)(param_2 + 0x9a0));
  HcReleaseEdca(param_1,param_2);
  hc_bcolor_release(param_2,*(undefined1 *)(param_2 + 0xa3d));
  os_zero_mem(param_2 + 0x98c,0x114);
  *(undefined4 *)(param_2 + 0x990) = 0;
  *(undefined4 *)(param_2 + 0x994) = 0;
  return;
}

